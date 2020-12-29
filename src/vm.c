#include <stdlib.h>
#include <time.h>
#include "vm.h"

static void ROM_load(vm_t *vm, const char *filename, uint16_t addr) {
    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    uint8_t *buffer = (uint8_t *)malloc(size * sizeof(uint8_t));

    fread(buffer, size, 1, file);
    RAM_load(&vm->ram, buffer, addr, size);

    fclose(file);
    free(buffer);
}

static void VM_decode(vm_t *vm) {
	uint8_t *byte1 = RAM_get(&vm->ram, vm->registers.PC);
	uint8_t *byte2 = RAM_get(&vm->ram, vm->registers.PC+1);
	vm->opcode = (*byte1 << 8) | *byte2;
}

void VM_init(vm_t *vm, const char *filename, bool ETI, uint16_t y, uint16_t x) {
	srand(time(NULL));

	Display_init(&vm->display, y, x);
	Instructions_init(&vm->instructions);
	Keypad_init(&vm->keypad, KEYPAD_DEFAULT_MAP);
	RAM_init(&vm->ram);
	Registers_init(&vm->registers);
	Stack_init(&vm->stack);

	vm->opcode = 0x0000;

	RAM_load(&vm->ram, VM_DEFAULT_SPRITES, 0x0000, VM_DEFAULT_SPRITES_SIZE);
	uint16_t addr = ETI ? RAM_ETI_LOAD_ADDRESS : RAM_DEFAULT_LOAD_ADDRESS;

	vm->registers.PC = addr;

	ROM_load(vm, filename, addr);
}

void VM_execute(vm_t *vm) {
	VM_decode(vm);
	Instructions_set(&vm->instructions, vm->opcode);

	uint16_t MSBit = vm->opcode & 0xf000;
    uint8_t LSByte = vm->opcode & 0x00ff;
    uint8_t LSBit = vm->opcode & 0x000f;

	vm->registers.PC += 2;

	if (vm->opcode == 0x00e0) {
        CLS(vm);
        return;
    }

    if (vm->opcode == 0x00ee) {
        RET(vm);
        return;
    }

	switch(MSBit) {
        case 0x0000:
            SYSAddr();
            return;
        case 0x1000:
            JPAddr(vm);
            return;
        case 0x2000:
            CALLAddr(vm);
            return;
        case 0x3000:
            SEVxByte(vm);
            return;
        case 0x4000:
            SNEVxByte(vm);
            return;
        case 0x5000:
            SEVxVy(vm);
            return;
        case 0x6000:
            LDVxByte(vm);
            return;
        case 0x7000:
            ADDVxByte(vm);
            return;
        case 0x8000:
            switch(LSBit) {
                case 0x00:
                    LDVxVy(vm);
                    return;
                case 0x01:
                    ORVxVy(vm);
                    return;
                case 0x02:
                    ANDVxVy(vm);
                    return;
                case 0x03:
                    XORVxVy(vm);
                    return;
                case 0x04:
                    ADDVxVy(vm);
                    return;
                case 0x05:
                    SUBVxVy(vm);
                    return;
                case 0x06:
                    SHRVx(vm);
                    return;
                case 0x07:
                    SUBNVxVy(vm);
                    return;
                case 0x0e:
                    SHLVx(vm);
                    return;
                default:
                    XXX(vm);
                    return;
            }
        case 0x9000:
            SNEVxVy(vm);
            return;
        case 0xa000:
            LDIAddr(vm);
            return;
        case 0xb000:
            JPV0Addr(vm);
            return;
        case 0xc000:
            RNDVxByte(vm);
            return;
        case 0xd000:
            DRWVxVyNibble(vm);
            return;
        case 0xe000:
			switch(LSByte) {
				case 0x9e:
            		SKPVx(vm);
					return;
				case 0xa1:
					SKNPVx(vm);
					return;
				default:
            		XXX(vm);
            		return;
			}
        case 0xf000:
            switch(LSByte) {
                case 0x07:
                    LDVxDT(vm);
                    return;
                case 0x0a:
                    LDVxK(vm);
                    return;
                case 0x15:
                    LDDTVx(vm);
                    return;
                case 0x18:
                    LDSTVx(vm);
                    return;
                case 0x1e:
                    ADDIVx(vm);
                    return;
                case 0x29:
                    LDFVx(vm);
                    return;
                case 0x33:
                    LDBVx(vm);
                    return;
                case 0x55:
                    LDIVx(vm);
                    return;
                case 0x65:
                    LDVxI(vm);
                    return;
                default:
                    XXX(vm);
                    return;
            }
        default:
            XXX(vm);
            return;
    }
}


void SYSAddr(void) {}

void CLS(vm_t *vm) {
    Display_clearscreen(&vm->display);
}

void RET(vm_t *vm) {
    vm->registers.PC = Stack_pop(&vm->stack, &vm->registers.SP);
}

void JPAddr(vm_t *vm) {
    vm->registers.PC = vm->instructions.nnn_addr;
}

void CALLAddr(vm_t *vm) {
    Stack_push(&vm->stack, &vm->registers.SP, vm->registers.PC);
    vm->registers.PC = vm->instructions.nnn_addr;
}

void SEVxByte(vm_t *vm) {
    if (vm->registers.Vx[vm->instructions.x] == vm->instructions.kk_byte) {
        vm->registers.PC += 2;
    }
}

void SNEVxByte(vm_t *vm) {
	if (vm->registers.Vx[vm->instructions.x] != vm->instructions.kk_byte) {
        vm->registers.PC += 2;
    }
}

void SEVxVy(vm_t *vm) {
    if (vm->registers.Vx[vm->instructions.x] == vm->registers.Vx[vm->instructions.y]) {
        vm->registers.PC += 2;
    }
}

void LDVxByte(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] = vm->instructions.kk_byte;
}

void ADDVxByte(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] += vm->instructions.kk_byte;
}

void LDVxVy(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] = vm->registers.Vx[vm->instructions.y];
}

void ORVxVy(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] |= vm->registers.Vx[vm->instructions.y];
}

void ANDVxVy(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] &= vm->registers.Vx[vm->instructions.y];
}

void XORVxVy(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] ^= vm->registers.Vx[vm->instructions.y];
}

void ADDVxVy(vm_t *vm) {
    vm->registers.Vx[0xf] = (vm->registers.Vx[vm->instructions.x] + vm->registers.Vx[vm->instructions.y]) > 0xff;
    vm->registers.Vx[vm->instructions.x] += vm->registers.Vx[vm->instructions.y];
}

void SUBVxVy(vm_t *vm) {
    vm->registers.Vx[0xf] = (vm->registers.Vx[vm->instructions.x] > vm->registers.Vx[vm->instructions.y]);
    vm->registers.Vx[vm->instructions.x] -= vm->registers.Vx[vm->instructions.y];
}

void SHRVx(vm_t *vm) {
    vm->registers.Vx[0xf] = vm->registers.Vx[vm->instructions.x] & 0x01;
    vm->registers.Vx[vm->instructions.x] /= 2;
}

void SUBNVxVy(vm_t *vm) {
    vm->registers.Vx[0xf] = vm->registers.Vx[vm->instructions.y] > vm->registers.Vx[vm->instructions.x];
    vm->registers.Vx[vm->instructions.x] = vm->registers.Vx[vm->instructions.y] - vm->registers.Vx[vm->instructions.x];
}

void SHLVx(vm_t *vm) {
    vm->registers.Vx[0xf] = vm->registers.Vx[vm->instructions.x] & 0x80;
    vm->registers.Vx[vm->instructions.x] *= 2;
}

void SNEVxVy(vm_t *vm) {
    if (vm->registers.Vx[vm->instructions.x] != vm->registers.Vx[vm->instructions.y]) {
        vm->registers.PC += 2;
    }
}

void LDIAddr(vm_t *vm) {
    vm->registers.I = vm->instructions.nnn_addr;
}

void JPV0Addr(vm_t *vm) {
    vm->registers.PC = vm->instructions.nnn_addr + vm->registers.Vx[0x0];
}

void RNDVxByte(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] = (rand() % 255) & vm->instructions.kk_byte;
}

void DRWVxVyNibble(vm_t *vm) {
    uint8_t *sprite = RAM_get(&vm->ram, vm->registers.I);
    vm->registers.Vx[0xf] = Display_set(&vm->display, vm->registers.Vx[vm->instructions.y], vm->registers.Vx[vm->instructions.x], sprite, vm->instructions.n_nibble);
}

void SKPVx(vm_t *vm) {
    if (Keypad_check(&vm->keypad, vm->registers.Vx[vm->instructions.x])) {
        vm->registers.PC += 2;
		Keypad_keyoff(&vm->keypad);
    }
}

void SKNPVx(vm_t *vm) {
	if (!Keypad_check(&vm->keypad, vm->registers.Vx[vm->instructions.x])) {
        vm->registers.PC += 2;
	}
}

void LDVxDT(vm_t *vm) {
    vm->registers.Vx[vm->instructions.x] = vm->registers.DT;
}

void LDVxK(vm_t *vm) {
    while(true) {
        int key;
        if ((key = getch()) == ERR)
            continue;

        int8_t value = Keypad_value(&vm->keypad, key);
        if (value != -1) {
            vm->registers.Vx[vm->instructions.x] = value;

            return;
        }
    }
}

void LDDTVx(vm_t *vm) {
    vm->registers.DT = vm->registers.Vx[vm->instructions.x];
}

void LDSTVx(vm_t *vm) {
    vm->registers.ST = vm->registers.Vx[vm->instructions.x];
}

void ADDIVx(vm_t *vm) {
    vm->registers.I += vm->registers.Vx[vm->instructions.x];
}

void LDFVx(vm_t *vm) {
    vm->registers.I = vm->registers.Vx[vm->instructions.x] * VM_DEFAULT_SPRITE_LENGTH;
}

void LDBVx(vm_t *vm) {
    uint8_t hundreds = vm->registers.Vx[vm->instructions.x] / 100;
    RAM_set(&vm->ram, vm->registers.I, hundreds);

    uint8_t tens = (vm->registers.Vx[vm->instructions.x] / 10) % 10;
    RAM_set(&vm->ram, vm->registers.I+1, tens);

    uint8_t units = vm->registers.Vx[vm->instructions.x] % 10;
    RAM_set(&vm->ram, vm->registers.I+2, units);
}

void LDIVx(vm_t *vm) {
    uint8_t i;
    for (i = 0; i <= vm->instructions.x; i++)
        RAM_set(&vm->ram, vm->registers.I+i, vm->registers.Vx[i]);
}

void LDVxI(vm_t *vm) {
    uint8_t i;
    for (i = 0; i <= vm->instructions.x; i++)
        vm->registers.Vx[i] = *RAM_get(&vm->ram, vm->registers.I+i);
}

void XXX(vm_t *vm) {
    printf("Invalid instruction: %x\n", vm->opcode);
}

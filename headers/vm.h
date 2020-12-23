#ifndef _VM_H_
#define _VM_H_

#include "display.h"
#include "keypad.h"
#include "instructions.h"
#include "ram.h"
#include "registers.h"
#include "stack.h"

static const uint8_t VM_DEFAULT_SPRITES_SIZE = 80;
static const uint8_t VM_DEFAULT_SPRITE_LENGTH = 5;
static const uint8_t VM_DEFAULT_SPRITES[VM_DEFAULT_SPRITES_SIZE] = {
	0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xf0, 0x10, 0xf0, 0x80, 0xf0, // 2
	0xf0, 0x10, 0xf0, 0x10, 0xf0, // 3
	0x90, 0x90, 0xf0, 0x10, 0x10, // 4
	0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
	0xf0, 0x80, 0xf0, 0x90, 0xf0, // 6
	0xf0, 0x10, 0x20, 0x40, 0x40, // 7
	0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
	0xf0, 0x90, 0xf0, 0x10, 0x10, // 9
	0xf0, 0x90, 0xf0, 0x90, 0x90, // A
	0xe0, 0x90, 0xe0, 0x90, 0xe0, // B
	0xf0, 0x80, 0x80, 0x80, 0xf0, // C
	0xe0, 0x90, 0x90, 0x90, 0xe0, // D
	0xf0, 0x80, 0xf0, 0x80, 0xf0, // E
	0xf0, 0x80, 0xf0, 0x80, 0x80, // F
};

struct vm {
	display_t display;
	instructions_t instructions;
	keypad_t keypad[KEYPAD_SIZE];
	ram_t ram;
	registers_t registers;
	stacks_t stack;
	uint16_t opcode;
};
typedef struct vm vm_t;

void SYSAddr(void);
void CLS(vm_t *);
void RET(vm_t *);
void JPAddr(vm_t *);
void CALLAddr(vm_t *);
void SEVxByte(vm_t *);
void SNEVxByte(vm_t *);
void SEVxVy(vm_t *);
void LDVxByte(vm_t *);
void ADDVxByte(vm_t *);
void LDVxVy(vm_t *);
void ORVxVy(vm_t *);
void ANDVxVy(vm_t *);
void XORVxVy(vm_t *);
void ADDVxVy(vm_t *);
void SUBVxVy(vm_t *);
void SHRVx(vm_t *);
void SUBNVxVy(vm_t *);
void SHLVx(vm_t *);
void SNEVxVy(vm_t *);
void LDIAddr(vm_t *);
void JPV0Addr(vm_t *);
void RNDVxByte(vm_t *);
void DRWVxVyNibble(vm_t *);
void SKPVx(vm_t *);
void SKNPVx(vm_t *);
void LDVxDT(vm_t *);
void LDVxK(vm_t *);
void LDDTVx(vm_t *);
void LDSTVx(vm_t *);
void ADDIVx(vm_t *);
void LDFVx(vm_t *);
void LDBVx(vm_t *);
void LDIVx(vm_t *);
void LDVxI(vm_t *);
void XXX(vm_t *);

void VM_init(vm_t *, const char *, bool, uint16_t, uint16_t);
void VM_execute(vm_t *);

#endif

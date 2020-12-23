#include <memory.h>
#include <time.h>
#include "instructions.h"

void Instructions_set(instructions_t *inst, const uint16_t opcode) {
	inst->nnn_addr = opcode & 0x0fff;
	inst->kk_byte = opcode & 0x00ff;
	inst->n_nibble = opcode & 0x000f;
	inst->x = (opcode & 0x0f00) >> 8;
	inst->y = (opcode & 0x00f0) >> 4;
}

void Instructions_init(instructions_t *inst) {
	memset(inst, 0, sizeof(instructions_t));
}

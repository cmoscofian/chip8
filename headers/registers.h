#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <stdint.h>

static const uint8_t REGISTERS_V_DEPTH = 16;

struct registers {
	int8_t SP;
	uint16_t PC;
	uint16_t I;
	uint8_t DT;
	uint8_t ST;
	uint8_t Vx[REGISTERS_V_DEPTH];
};
typedef struct registers registers_t;

void Registers_init(registers_t *);

#endif

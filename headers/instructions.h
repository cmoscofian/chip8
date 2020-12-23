#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <stdint.h>

struct instructions {
	uint16_t nnn_addr;
	uint8_t kk_byte;
	uint8_t x;
	uint8_t y;
	uint8_t n_nibble;
};
typedef struct instructions instructions_t;

void Instructions_set(instructions_t *, const uint16_t);
void Instructions_init(instructions_t *);

#endif

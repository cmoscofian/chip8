#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>

static const uint8_t STACK_DEPTH = 16;

struct stack {
	uint16_t stack[STACK_DEPTH];
};
typedef struct stack stacks_t;

void Stack_init(stacks_t *);
void Stack_push(stacks_t *, int8_t *, uint16_t);
uint16_t Stack_pop(stacks_t *, int8_t *);

#endif

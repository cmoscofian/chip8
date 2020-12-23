#include <memory.h>
#include "stack.h"

void Stack_init(stacks_t *stack) {
	memset(stack, 0, sizeof(stacks_t));
}

void Stack_push(stacks_t *stack, int8_t *sp, const uint16_t data) {
	*sp += 1;
	stack->stack[*sp] = data;
}

uint16_t Stack_pop(stacks_t *stack, int8_t *sp) {
	uint16_t temp = stack->stack[*sp];
	*sp -= 1;
	return temp;
}

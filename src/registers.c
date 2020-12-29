#include <memory.h>
#include "registers.h"

void Registers_init(registers_t *registers) {
	memset(registers, 0, sizeof(registers_t));
	registers->SP = -1;
}

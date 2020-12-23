#include <memory.h>
#include "ram.h"

void RAM_init(ram_t *ram) {
	memset(ram, 0, sizeof(ram_t));
}

void RAM_load(ram_t *ram, const uint8_t *data, const uint16_t index, const uint16_t size) {
	memcpy(&ram->ram[index], data, size);
}

uint8_t *RAM_get(ram_t *ram, const uint16_t index) {
	return &ram->ram[index];
}

void RAM_set(ram_t *ram, const uint16_t index, const uint8_t data) {
	ram->ram[index] = data;
}

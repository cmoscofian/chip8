#ifndef _RAM_H_
#define _RAM_H_

#include <stdint.h>

static const uint16_t RAM_SPRITES_LOAD_ADDRESS = 0X0000;
static const uint16_t RAM_MAX_SIZE = 0xfff+1;
static const uint16_t RAM_DEFAULT_LOAD_ADDRESS = 0x0200;
static const uint16_t RAM_ETI_LOAD_ADDRESS = 0x0600;

struct ram {
	uint8_t ram[RAM_MAX_SIZE];
};
typedef struct ram ram_t;

void RAM_init(ram_t *);
void RAM_load(ram_t *, const uint8_t *, const uint16_t index, const uint16_t size);
uint8_t *RAM_get(ram_t *, const uint16_t);
void RAM_set(ram_t *, const uint16_t, const uint8_t);

#endif

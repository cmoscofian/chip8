#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <stdbool.h>
#include <stdint.h>

static const uint8_t KEYPAD_SIZE = 16;

static const char KEYPAD_DEFAULT_MAP[KEYPAD_SIZE] = {
	'1', '2', '3', '4',
	'q', 'w', 'e', 'r',
	'a', 's', 'd', 'f',
	'z', 'x', 'c', 'v',
};

static const uint8_t KEYPAD_STD_KEYS[KEYPAD_SIZE] = {
	0x1, 0x2, 0x3, 0xc,
	0x4, 0x5, 0x6, 0xd,
	0x7, 0x8, 0x9, 0xe,
	0xa, 0x0, 0xb, 0xf,
};

struct keypad {
	char key;
	uint8_t value;
	bool state;
};
typedef struct keypad keypad_t;

void Keypad_init(keypad_t keypad[KEYPAD_SIZE], const char *);
void Keypad_keyon(keypad_t keypad[KEYPAD_SIZE], const char);
void Keypad_keyoff(keypad_t keypad[KEYPAD_SIZE], const char);
keypad_t *Keypad_get(keypad_t keypad[KEYPAD_SIZE], const uint8_t);
int8_t Keypad_value(keypad_t keypad[KEYPAD_SIZE], const char);

#endif

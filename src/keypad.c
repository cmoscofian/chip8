#include <memory.h>
#include "keypad.h"

void Keypad_init(keypad_t *keypad, const char *map) {
	memset(keypad, 0, sizeof(keypad_t));
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++) {
		keypad->keys[i].key = map[i];
		keypad->keys[i].value = KEYPAD_STD_KEYS[i];
	}
}

void Keypad_keyon(keypad_t *keypad, const char key) {
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++)
		if (keypad->keys[i].key == key) {
			keypad->keyon = keypad->keys[i].value;
			return;
		}
}

void Keypad_keyoff(keypad_t *keypad) {
	keypad->keyon = 0;
}

bool Keypad_check(keypad_t *keypad, const uint8_t value) {
	return keypad->keyon == value;
}

int8_t Keypad_value(keypad_t *keypad, const char key) {
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++) {
		if (keypad->keys[i].key == key) {
			return keypad->keys[i].value;
		}
	}

	return -1;
}

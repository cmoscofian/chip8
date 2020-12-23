#include <memory.h>
#include "keypad.h"

void Keypad_init(keypad_t keypad[KEYPAD_SIZE], const char *map) {
	memset(keypad, 0, sizeof(keypad_t)*KEYPAD_SIZE);
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++) {
		keypad[i].key = map[i];
		keypad[i].value = KEYPAD_STD_KEYS[i];
	}
}

void Keypad_keyon(keypad_t keypad[KEYPAD_SIZE], const char key) {
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++)
		if (keypad[i].key == key) {
			keypad[i].state = true;
			return;
		}
}

void Keypad_keyoff(keypad_t keypad[KEYPAD_SIZE], const char key) {
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++)
		if (keypad[i].key == key) {
			keypad[i].state = false;
			return;
		}
}

keypad_t *Keypad_get(keypad_t keypad[KEYPAD_SIZE], const uint8_t value) {
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++) {
		if (keypad[i].value == value) {
			return &keypad[i];
		}
	}

	return NULL;
}

int8_t Keypad_value(keypad_t keypad[KEYPAD_SIZE], const char key) {
	int i;
	for (i = 0; i < KEYPAD_SIZE; i++) {
		if (keypad[i].key == key) {
			return keypad[i].value;
		}
	}

	return -1;
}

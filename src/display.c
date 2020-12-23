#include <memory.h>
#include <ncurses.h>
#include <stdlib.h>

#include "display.h"

void Display_init(display_t *display, const uint16_t y, const uint16_t x) {
	memset(display, 0, sizeof(display_t));
	display->win = newwin(DISPLAY_HEIGHT, DISPLAY_WIDTH, y, x);
	if (display->win == NULL) {
		printf("Unable to generate a new window");
		exit(1);
	}

	box(display->win, 0, 0);
	refresh();
}

bool Display_set(display_t *display, const uint8_t y, const uint8_t x, const uint8_t *sprite, const uint8_t nibble) {
	uint8_t ly, lx;

	bool collision = false;

	for (ly = 0; ly < nibble; ly++) {
		uint8_t pixel = sprite[ly];
		for (lx = 0; lx < 8; lx++) {
			if (!(pixel & (0x80 >> lx)))
				continue;

			if (display->pixels[((x + lx) % DISPLAY_WIDTH) + (((y + ly) % DISPLAY_HEIGHT) * DISPLAY_WIDTH)])
				collision = true;

			display->pixels[((x + lx) % DISPLAY_WIDTH) + (((y + ly) % DISPLAY_HEIGHT) * DISPLAY_WIDTH)] ^= 1;
		}
	}

	display->refresh = true;

	return collision;
}

void Display_draw(display_t *display) {
	uint16_t y, x;

	for (y = 0; y < DISPLAY_HEIGHT; y++)
		for (x = 0; x < DISPLAY_WIDTH; x++)
			if (display->pixels[x + (y * DISPLAY_WIDTH)]) {
				wattron(display->win, A_REVERSE);
				mvwaddch(display->win, y, x, ' ');
				wattroff(display->win, A_REVERSE);
			} else {
				mvwaddch(display->win, y, x, ' ');
			}

	wrefresh(display->win);
	display->refresh = false;
}

void Display_clearscreen(display_t *display) {
	memset(display->pixels, false, sizeof(display->pixels));
	display->refresh = true;
}

void Display_cleanup(display_t *display) {
	delwin(display->win);
}

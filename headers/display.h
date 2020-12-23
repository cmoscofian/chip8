#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

static const uint16_t DISPLAY_HEIGHT = 32;
static const uint16_t DISPLAY_WIDTH = 64;

struct display {
	WINDOW *win;
	bool pixels[DISPLAY_HEIGHT*DISPLAY_WIDTH];
	bool refresh;
};
typedef struct display display_t;

void Display_init(display_t *, const uint16_t y, const uint16_t x);
bool Display_set(display_t *, const uint8_t y, const uint8_t x, const uint8_t *sprite, const uint8_t nibble);
void Display_draw(display_t *);
void Display_clearscreen(display_t *);
void Display_cleanup(display_t *);

#endif

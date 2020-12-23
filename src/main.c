#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vm.h"

static void splash_screen(uint16_t y, uint16_t x) {
	WINDOW *window = newwin(DISPLAY_HEIGHT, DISPLAY_WIDTH, y, x);
	if (window == NULL) {
		printf("Unable to generate a new window");
		exit(1);
	}

	box(window, 0, 0);
	refresh();

	nodelay(window, 0);

	getmaxyx(window, y, x);
	mvwaddstr(window, y / 2 - 1, x / 2 - 12, "Welcome to the CHIP8 XP!");
	mvwaddstr(window, y / 2 + 1, x / 2 - 14, "Press any key to continue...");

	wrefresh(window);

	wgetch(window);
	delwin(window);
}

int main(const int argc, const char **argv) {
	if (argc < 2) {
		printf("Usage: %s <path_to_rom>", argv[0]);
		return -1;
	}

	initscr();
	curs_set(0);
	noecho();
	nodelay(stdscr, 1);

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	uint16_t y = yMax / 2 - DISPLAY_HEIGHT / 2;
	uint16_t x = xMax / 2 - DISPLAY_WIDTH / 2;

	splash_screen(y, x);

	vm_t vm;
	VM_init(&vm, argv[1], false, y, x);

	while (1) {
		int c;
		if ((c = getch()) != ERR) {
			switch (c) {
			case 27:
				Display_cleanup(&vm.display);
				endwin();
				return 0;
			default:
				Keypad_keyon(vm.keypad, c);
				break;
			}
		}

		VM_execute(&vm);

		if (vm.registers.DT > 0) {
			vm.registers.DT--;
		}

		if (vm.registers.ST > 0) {
			puts("\a");
			vm.registers.ST--;
		}

		if (vm.display.refresh) {
			Display_draw(&vm.display);
		}

		usleep(2000);
	}

	endwin();
}

#include <memory.h>
#include "debugger.h"

void Debugger_init(debugger_t *debugger, vm_t *vm) {
	memset(debugger, 0, sizeof(debugger_t));
	debugger->win = newwin(DISPLAY_HEIGHT, DISPLAY_WIDTH, 0, DISPLAY_WIDTH+1);
	debugger->vm = vm;
	box(debugger->win, 0, 0);
	refresh();
}

void Debugger_draw(debugger_t *debugger) {
	uint8_t i;
	for (i = 0; i < REGISTERS_V_DEPTH; i++)
		mvwprintw(debugger->win, 2+i, 3, "V%x: 0x%.2x (%3u)", i, debugger->vm->registers.Vx[i], debugger->vm->registers.Vx[i]);

	mvwprintw(debugger->win, 2, 32, "PC: 0x%.4x (%5u)", debugger->vm->registers.PC, debugger->vm->registers.PC);
    mvwprintw(debugger->win, 3, 32, "IR: 0x%.4x (%5i)", debugger->vm->registers.I);
    mvwprintw(debugger->win, 4, 32, "SP: 0x%.4x (%3i)", debugger->vm->registers.SP, debugger->vm->registers.SP);
    mvwprintw(debugger->win, 6, 32, "ST: 0x%.2x (%3u)", debugger->vm->registers.ST, debugger->vm->registers.ST);
    mvwprintw(debugger->win, 7, 32, "DT: 0x%.2x (%3u)", debugger->vm->registers.DT, debugger->vm->registers.DT);
	mvwprintw(debugger->win, 9, 32, "Opcode: 0x%.4x", debugger->vm->opcode);
	// mvwprintw(debugger->win, 10, 32, "Current instruction: 0x%.4x", debugger->vm);
	mvwprintw(debugger->win, 12, 32, "Keyon: 0x%.2x", debugger->vm->keypad.keyon);

	wrefresh(debugger->win);
}

void Debugger_cleanup(debugger_t *debugger) {
	delwin(debugger->win);
}

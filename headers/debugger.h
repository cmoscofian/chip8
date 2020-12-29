#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <ncurses.h>
#include "vm.h"

struct debugger {
	WINDOW *win;
	vm_t *vm;
};
typedef struct debugger debugger_t;

void Debugger_init(debugger_t *, vm_t *);
void Debugger_draw(debugger_t *);
void Debugger_cleanup(debugger_t *);

#endif

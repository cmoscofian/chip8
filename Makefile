CC = clang
CFLAGS = -g -Wall -Wextra
INCLUDE = -I headers
NCURSES = -l ncurses

all: clear bin/chip

bin/chip: src/main.c build/debugger.o build/display.o build/instructions.o build/keypad.o build/ram.o build/registers.o build/stack.o build/vm.o
	${CC} ${CFLAGS} ${INCLUDE} ${NCURSES} $^ -o $@

build/%.o: src/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $^ -o $@

.phony: clear
clear:
	rm -rf bin/* build/*

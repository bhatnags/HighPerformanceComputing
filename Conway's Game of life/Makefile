CC=gcc
FLAGS=-Wall -Wextra -Wshadow -std=c99 -lm
BIN=/usr/bin

life: life.c
	${CC} life.c ${FLAGS} -o life

clean:
	rm life

install: game
	cp -v life ${BIN}

uninstall:
	rm -v ${BIN}life


# Makefile for Project 4: Minesweeper


minesweeper:	minesweeper.o io.o game.o
	gcc -Wall -g -std=c99 -o minesweeper minesweeper.o io.o game.o

minesweeper.o:	minesweeper.c io.h game.h
	gcc -Wall -g -std=c99 -c minesweeper.c

io.o:	io.c io.h
	gcc -Wall -g -std=c99 -c io.c

game.o:	game.c game.h
	gcc -Wall -g -std=c99 -c game.c

clean:
	rm -f minesweeper
	rm -f minesweeper.o
	rm -f io.o
	rm -f game.o

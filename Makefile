

CC=gcc
CFLAGS=-g -std=c99 -Wall
LIBS=csfml-system csfml-window csfml-graphics csfml-audio 

all:
	#make -C src
	$(CC) $(CFLAGS) $(addprefix -l, $(LIBS)) -c src/swps.c -o bin/swps.o
	$(CC) $(addprefix -l, $(LIBS)) bin/* -o swps

clean:
	rm -R bin/*

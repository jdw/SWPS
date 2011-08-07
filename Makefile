

CC=gcc
CFLAGS=-g -std=c99 -Wall
LIBS=csfml-system csfml-window csfml-graphics csfml-audio 
TARGET=swps

default:
	#make -C src
	$(CC) $(CFLAGS) $(addprefix -l, $(LIBS)) -c src/swps.c -o bin/swps.o
	$(CC) $(addprefix -l, $(LIBS)) bin/* -o $(TARGET)

clean:
	rm $(TARGET)
	rm -R bin/*

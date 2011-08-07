
LIBS=csfml-system csfml-window csfml-graphics isfml-audio
SOURCES := $((wildcard *.c)
OBJS := $(patsubst %.c %.o  $(SOURCES))
DIRS = scenes
CC = gcc
CFLAGS = -g -Wall -std=99

all:
	$(CC) $(CFLAGS) $(addprefix -l, $(LIBS)) -c main.c -o ../bin/main.o
	$(foreach dir, $(DIRS), make -C $(dir))
	$(CC) $(CFLAGS) $(OBJS)

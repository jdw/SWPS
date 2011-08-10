
LIBS=csfml-system csfml-window csfml-graphics csfml-audio
SOURCES := $((wildcard *.c)
OBJS := $(patsubst %.c, %.o,  $(SOURCES))
DIRS = scenes stuff
CC = gcc
CFLAGS = -g -Wall -std=c99

all:
	$(foreach DIR, $(DIRS), make -C $(DIR))
	$(CC) $(CFLAGS) $(addprefix -l, $(LIBS)) -c main.c -o ../bin/main.o

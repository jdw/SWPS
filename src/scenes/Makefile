
LIBS=csfml-system csfml-window csfml-graphics csfml-audio
SOURCES := $((wildcard *.c)
OBJS := $(patsubst %.c, %.o,  $(SOURCES))
DIRS =
CC = gcc
CFLAGS = -g -Wall -std=c99

all: $(OBJS)
	$(foreach DIR, $(DIRS), make -C $(DIR))

%.c: %.o
	$(CC) $(CFLAGS) -c $< -o ../../bin/$@

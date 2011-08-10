

CC=gcc
CFLAGS=-g -std=c99 -Wall
LIBS=csfml-system csfml-window csfml-graphics csfml-audio 
TARGET=swps
SOURCES = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,%.o, $(SOURCES))
#OBJS = main.o

swps: $(OBJS)
	$(CC) $(CFLAGS) $(addprefix -l,$(LIBS)) $(addprefix bin/,$^) -o $@

%.o : 
	$(CC) $(CFLAGS) -c src/$(patsubst %.o,%.c, $@) -o bin/$@ -Isrc/

clean:
	rm -f $(TARGET)
	rm -Rf bin/*

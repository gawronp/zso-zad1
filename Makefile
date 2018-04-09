CFLAGS=-Wall -Wextra -Werror -pedantic -std=gnu11
SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: emu

emu: $(OBJECTS)
	$(CC) $(CFLAGS) -o emu $(OBJECTS) -lncurses

.%.depends: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.o emu

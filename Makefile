CFLAGS=-std=gnu11

all: emu

emu: main.o
	$(CC) $(CFLAGS) -o emu main.o -lncurses

.%.depends: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o emu

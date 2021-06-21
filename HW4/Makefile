CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=gnu99 -g
LIBS = -lm
DEPS = boot.h
OBJS = boot.o test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

all: makeFileSystem

makeFileSystem: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o makeFileSystem
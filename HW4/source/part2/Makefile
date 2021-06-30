CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=gnu99 -g
LIBS = -lm
DEPS = data_structures.h fat12.h
OBJS = fat12.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

all: makeFileSystem

makeFileSystem: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o makeFileSystem
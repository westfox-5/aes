CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g

all: main

main: main.o key.o block.o state.o
	$(CC) $(CFLAGS) -o aes main.o key.o block.o state.o

main.o: main.c aes.h
	$(CC) $(CFLAGS) -c main.c

block.o: block.c block.h
	$(CC) $(CFLAGS) -c block.c

key.o: key.c key.h
	$(CC) $(CFLAGS) -c key.c

state.o: state.c state.h
	$(CC) $(CFLAGS) -c state.c

clean:
	$(RM) aes *.o *.a *~

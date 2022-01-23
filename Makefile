CC=gcc
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) -o aes main.c aes.c

clean:
	$(RM) aes

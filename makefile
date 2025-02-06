CC=gcc
CFLAGS=-Wall -Wextra

all: main.out

main.out: main.c
	$(CC) $(CFLAGS) main.c -o main.out

CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ggdb

all: main.out

main.out: main.c
	$(CC) $(CFLAGS) main.c -o main.out

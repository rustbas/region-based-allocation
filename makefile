CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ggdb

all: demo.out

demo.out: demo.c
	$(CC) $(CFLAGS) demo.c -o demo.out

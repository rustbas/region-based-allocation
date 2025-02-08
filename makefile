CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ggdb

demo: demo.out

demo.out: demo.c
	$(CC) $(CFLAGS) demo.c -o demo.out

clean:
	rm -f demo.out

.PHONY: demo clean

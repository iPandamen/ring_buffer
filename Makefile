CC = gcc
CFLAGS  = -Wall -g -O2 -std=c99


all: test


test: ring_buffer.c test.c
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f test



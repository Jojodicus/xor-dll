.PHONY: all test build clean

CC = gcc
CFLAGS = -std=c17 -O2 -pedantic -Wall -pipe

all: build test

build: build/xor.s

test: build/test

clean:
	find build -type f -not -name .gitkeep -delete


build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/xor.s: build/xor.o
	$(CC) $(CFLAGS) -shared $^ -o $@

build/test: build/test.o build/xor.o
	$(CC) $(CFLAGS) $^ -o $@

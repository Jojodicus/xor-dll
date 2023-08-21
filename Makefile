.PHONY: test build clean

CC = gcc
CFLAGS = -O2 -pedantic -Wall -pipe

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

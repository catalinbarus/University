CC = gcc
CFLAGS = -Wall
LDLIBS = 

all: ops

ops: mul.o add.o ops.o
	 $(CC) $^ -o $@ 

mul.o: mul.c mul.h
add.o: add.c add.h
ops.o: ops.c

clean:
	rm -rf *.o ops


all: exec
exec: io.o
	gcc bot2.c io.o -o bot2
io.o: io.c
	gcc io.c -c
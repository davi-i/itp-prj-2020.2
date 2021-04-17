PARAMS = -fsanitize=address,undefined -g

all: exec
exec: io.o
	gcc vem_com_o_boBOTantan.c io.o -o bot $(PARAMS)
io.o: io.c
	gcc io.c -c $(PARAMS)
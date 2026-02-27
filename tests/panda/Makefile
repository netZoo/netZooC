# Description:
#	This is a simple Makefile to compile the test that checks if two PANDA networks are identical
#	using the .pairs format of the network
#
# Authors:
#	Marouen Ben Guebila 5/19
CC     = gcc
OBJ    = test-panda.o
CFLAGS = -Wall -Os

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test-panda: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f *.o test-panda

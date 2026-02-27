# Description:
#	This is a simple Makefile to compile the test that checks if two PUMA networks are identical
#	using the .pairs format of the network
#
# Authors:
#	Marouen Ben Guebila 10/19
CC     = gcc
OBJ    = test-puma.o
CFLAGS = -Wall -Os

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test-puma: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f *.o test-puma

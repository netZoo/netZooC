# Description:
#	This is a simple Makefile to compile the test that checks if two PANDA network are identical
#	using the .pairs format of the network
#
# Authors:
#	Marouen Ben Guebila 5/19
CC     = gcc 
OBJ    = test-panda.o
INCLUDE= $(HOME)/netzoo-c/netzoo-c/panda
CFLAGS = -I$(INCLUDE) -Wall -fprofile-arcs -coverage

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test-panda: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm -lncurses -Os

clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info

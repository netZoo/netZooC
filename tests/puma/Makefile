# Description:
#	This is a simple Makefile to compile the test that checks if two PUMA networks are identical
#	using the .pairs format of the network
#
# Authors:
#	Marouen Ben Guebila 10/19
CC     = gcc 
OBJ    = test-puma.o
INCLUDE= $(HOME)/netZooC/netZooC/puma
CFLAGS = -I$(INCLUDE) -Wall -fprofile-arcs

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test-panda: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm -lncurses -Os

clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info

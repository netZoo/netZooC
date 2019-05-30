CC     = gcc 
OBJ    = test-panda.o
INCLUDE= $(HOME)/netzoo-c/netzoo-c/panda
CFLAGS = -I$(INCLUDE) -Wall -ftest-coverage -fprofile-arcs

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test-panda: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm -lncurses -Os

clean :
	rm  *.o  *.asm  *.lst *.sym *.rel *.s *.gc* -f *.info

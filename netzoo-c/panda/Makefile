# Description:
#             This is a simple Makefile to compile PANDA in c++
# Authors:
#             Kimberley Glass, Marouen Ben Guebila 05/2019

PANDA: PANDA_v2.c
	g++ -O3 -coverage -o PANDA PANDA_v2.c

test: 
	echo "Running PANDA test"
	./PANDA -e ../../tests/ToyData/ToyExpressionData.txt -m ../../tests/ToyData/ToyMotifData.txt -o ToyOutput
	diff -q ToyOutput_FinalNetwork.pairs ../../tests/ToyData/ToyOutput_FinalNetwork.pairs; \
	RETVAL=$$?; \
	if [ $$RETVAL -eq 0 ]; then \
		echo "SAME"; \
	else \
		echo "NOT SAME"; \
	fi
	#cmp --silent ToyOutput_FinalNetwork.pairs ../../tests/ToyData/ToyOutput_FinalNetwork.pairs && echo '### SUCCESS: Files Are Identical! ###' || echo '### WARNING: Files Are Different! ###'
	
clean:
	rm *.o *.gcno *.gcda *.pairs

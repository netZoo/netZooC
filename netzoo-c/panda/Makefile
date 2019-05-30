# Description:
#             This is a simple Makefile to compile PANDA in c++
# Authors:
#             Kimberley Glass, Marouen Ben Guebila 05/2019

PANDA: PANDA_v2.c
	g++ -O3 -coverage -o PANDA PANDA_v2.c

test: 
	echo "Running PANDA test"
	./PANDA -e ../../tests/ToyData/ToyExpressionData.txt -m ../../tests/ToyData/ToyMotifData.txt -o ToyOutput
	if diff ToyOutput_FinalNetwork.pairs ../../tests/ToyData/ToyOutput_FinalNetwork.pairs > /dev/null
	then 
		echo '### SUCCESS: Files Are Identical! ###' 
	else
		echo '### WARNING: Files Are Different! ###'
	fi

clean:
	rm *.o *.gcno *.gcda *.pairs

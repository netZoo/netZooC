/*
Description: 
	Unit test for the PANDA algorithm.

Authors:
	Marouen Ben Guebila 5/19

Reference:
	https://github.com/deftio/travis-ci-cpp-example
*/
#include <stdio.h>
#include "PANDA_v2.h"

#define S_OK (0)
#define E_FAIL (-1)

int test_Initialize() {

	if ( Initialize((REGULATION *) &Regulation, (GENES *) &Genes) != 0)
		return E_FAIL;

	return S_OK;
}

int run_tests(){
	if(E_FAIL == test_Initialize()){
		printf("failed test_Initialize()\n");
		return E_FAIL;
	}

	return S_OK;
}

int main(){

	int result;

	printf("Running Panda test ..\n");
	result = run_tests();

	if(result == S_OK)
		printf("test passed.\n");
	else
		printf("test failed.\n");

return result; //(0 means passed in travis)


}

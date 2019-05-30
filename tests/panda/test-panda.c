/*
Description: 
	Unit test for the PANDA algorithm.

Authors:
	Marouen Ben Guebila 5/19

Reference:
	https://github.com/deftio/travis-ci-cpp-example
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define S_OK (0)
#define E_FAIL (-1)
#define BUFSIZE 10000

FILE *fid1;
FILE *fid2;

int test_PANDA(char filename1[], char filename2[], int decimal) {
	/*
	Tests if two PANDA networks are the same, with a tolerance on the edges
	*/
	float D1,D2,P1,P2;
	char temp1[BUFSIZE];
	char temp2[BUFSIZE];
	char temp11[32];
	char temp22[32];
	int cnt=0;

        if((fid1=fopen(filename1, "r"))==NULL)
        {
                printf("ERROR OPENING FILE TEST 1\n");
                exit(1);
        }

	if((fid2=fopen(filename2, "r"))==NULL)
        {
                printf("ERROR OPENING FILE TEST 2\n");
                exit(1);
        }

	fprintf(stderr, "Reading in test data! \n");

        while( (fscanf(fid1, "%s\t%s\t%f\t%f", temp1,temp11,&P1,&D1)==4) & (fscanf(fid2, "%s\t%s\t%f\t%f", temp2,temp22,&P2,&D2)==4) ) //!feof(fid))
	{
		cnt+=1;
 		if(floorf(D2* pow(10,decimal)) / pow(10,decimal) != floorf(D1* pow(10,decimal)) / pow(10,decimal) ){
			printf("D1 is %f \n", D1);
			printf("D2 is %f \n", D2);
			printf("line is %d", cnt);
			return E_FAIL;
		}
	}

	return S_OK;
}

int run_tests(char filename1[], char filename2[]){
	int decimal=2; //round decimal for comparison of two floats
	
	if(E_FAIL == test_PANDA(filename1, filename2, decimal)){
		printf("failed test_PANDA()\n");
		return E_FAIL;
	}

	return S_OK;
}

int main(int argc, char **argv){

	int result;

	printf("Running Panda test ..\n");

	result = run_tests(argv[1], argv[2]);

	if(result == S_OK)
		printf("test passed.\n");
	else
		printf("test failed.\n");

return result; //(0 means passed in travis)


}

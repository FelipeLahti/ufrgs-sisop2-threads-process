#include "stdlib.h"
#include "../lib/matrix.c"
#include "lib/multiply_matrix_process.c"

int getNumberOfProcess(int argc, char const *argv[]){
	int i;
	
	if (argc < 2) {
		printf("You must have to pass the number of process.");
		exit(1);
	} 
	return atoi(argv[1]);
}

int main(int argc, char const *argv[])
{
	Matrix *m1 = getMatrixFromFile("in1.txt");
	Matrix *m2 = getMatrixFromFile("in2.txt");

	int process = getNumberOfProcess(argc, argv);

	printf("Multiplying matrices using %d process\n", process);

	return 0;
}
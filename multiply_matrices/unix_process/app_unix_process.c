#include "stdlib.h"
#include "../lib/matrix.c"
#include "lib/multiply_matrix_process.c"

int main(int argc, char const *argv[])
{
	Matrix *m1 = getMatrixFromFile("in1.txt");
	Matrix *m2 = getMatrixFromFile("in2.txt");

	int process = getNumberOfProcessOrThreadNumber(argc, argv);

	printf("Multiplying matrices using %d process\n", process);

	Matrix result = multipleMatrixUsingProcess(*m1,*m2, process);

	printMatrix(result);

	return 0;
}
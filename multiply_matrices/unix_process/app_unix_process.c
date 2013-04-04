#include "stdlib.h"
#include "../lib/matrix.c"
#include "../lib/params.c"
#include "lib/multiply_matrix_process.c"

int main(int argc, char const *argv[])
{
	Matrix *m1 = getMatrixFromFile(getFileMatrixName(argc, argv, 1));
	Matrix *m2 = getMatrixFromFile(getFileMatrixName(argc, argv, 2));

	int process = getNumberOfProcessOrThreadNumber(argc, argv);

	printf("Multiplying matrices using %d process\n", process);

	Matrix result = multipleMatrixUsingProcess(*m1,*m2, process);

	printMatrix(result);

	return 0;
}
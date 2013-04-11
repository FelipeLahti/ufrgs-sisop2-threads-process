#include "stdlib.h"
#include "../lib/matrix.c"
#include "../lib/params.c"
#include "lib/multiply_matrix_pthreads.c"

int main(int argc, char const *argv[])
{
	Matrix *m1 = readMatrix(getFileMatrixName(argc, argv, 1));
	Matrix *m2 = readMatrix(getFileMatrixName(argc, argv, 2));
    
	int process = getNumberOfProcessOrThreadNumber(argc, argv);
    
	Matrix result = multiplyMatrixUsingPthreads(*m1,*m2, process);
    
    writeMatrix("out.txt", result);
    
	return 0;
}
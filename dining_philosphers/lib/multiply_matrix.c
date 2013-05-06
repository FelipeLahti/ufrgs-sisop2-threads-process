#include "matrix.c"

Matrix multipleMatrix(Matrix m1, Matrix m2){
	Matrix result;
	result.lines = m1.lines;
	result.columns = m2.columns;
	allocMatrix(&result);

	int i,j;
	for (i = 0; i < result.lines; ++i) {
		for (j = 0; j < result.columns; ++j) {
			result.matrix[i][j] = multiplyLineColumn(i, j, m1, m2);
		}
	}

	return result;
}
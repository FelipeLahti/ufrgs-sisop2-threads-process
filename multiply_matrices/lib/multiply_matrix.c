#include "matrix.c"

Matrix multipleMatrix(Matrix m1, Matrix m2){
	Matrix result;
	result.width = m1.width;
	result.height = m2.height;
	allocMatrix(&result);

	int i,j;
	for (i = 0; i < result.width; ++i) {
		for (j = 0; j < result.height; ++j) {
			result.matrix[i][j] = multiplyLineColumn(i, j, m1, m2);
		}
	}

	return result;
}
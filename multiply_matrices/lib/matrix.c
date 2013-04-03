#include "stdio.h"
#include "stdlib.h"

typedef struct {
	int width;
	int height;
	int **matrix;
} Matrix;

void allocMatrix(Matrix *matrix){
	matrix->matrix = calloc(matrix->width, sizeof(int*));	
	int i = 0;		
	for(i = 0; i < matrix->height; i++) {
	    matrix->matrix[i] = calloc(matrix->height, sizeof(int));
	}
}

Matrix prepareMatrixMultiplicationResult(Matrix m1, Matrix m2) {
	Matrix result;
	result.width = m1.width;
	result.height = m2.height;
	allocMatrix(&result);
	return result;
}

int matrixAreEqual(Matrix matrix1, Matrix matrix2){
	if(	matrix1.width == matrix2.width && 
		matrix2.height == matrix2.height) {
		int i, j;
		for (i = 0; i < matrix1.width; ++i) {
			for (j = 0; j < matrix1.height; ++j) {
				if (matrix1.matrix[i][j] != matrix2.matrix[i][j]) {
					return 0;
				}
 			}
		}

		return 1;
	}

	return 0;
}

void printMatrix(Matrix matrix) {
	int i,j;
	for(i = 0; i < matrix.width; ++i){
		for(j = 0; j < matrix.height; ++j){
			printf("%d ", matrix.matrix[i][j]);
		}
		printf("\n");
	}
}

int multiplyLineColumn(int line, int column, Matrix m1, Matrix m2) {
	int sum = 0;
	int i,j;
	for (i = 0; i < m1.width; ++i) {
		sum += m1.matrix[line][i] * m2.matrix[i][column];
	}
	return sum;
}
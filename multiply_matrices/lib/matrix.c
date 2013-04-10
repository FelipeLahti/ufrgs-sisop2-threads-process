#include "stdio.h"
#include "stdlib.h"

#ifndef	_MATRIX_
#define	_MATRIX_

typedef struct {
	int lines;
	int columns;
	int **matrix;
} Matrix;

void allocMatrix(Matrix *matrix){
	matrix->matrix = calloc(matrix->lines, sizeof(int*));	
	int i = 0;		
	for(i = 0; i < matrix->columns; i++) {
	    matrix->matrix[i] = calloc(matrix->columns, sizeof(int));
	}
}

int multiplyLineColumn(int line, int column, Matrix m1, Matrix m2) {
	int sum = 0;
	int i;
	for (i = 0; i < m1.lines; ++i) {
		sum += m1.matrix[line][i] * m2.matrix[i][column];
	}
	return sum;
}

Matrix prepareMatrixMultiplicationResult(Matrix m1, Matrix m2) {
	Matrix result;
	result.lines = m1.lines;
	result.columns = m2.columns;
	allocMatrix(&result);
	return result;
}

Matrix *readMatrix(char *fileName) {
	Matrix *matrix = calloc(1, sizeof(Matrix));
	int lines, columns;
	int i,j,temp;

	FILE *file = fopen(fileName, "r");
	
	if ( file == NULL ) {
		printf("Could not read file: %s\n", fileName);
		exit(1);
	}

	fscanf(file, "LINHAS = %d\n", &lines);
	fscanf(file, "COLUNAS = %d\n", &columns);
	
	matrix->lines = lines;
	matrix->columns = columns;
	allocMatrix(matrix);

	for (i = 0; i < lines; ++i) {
		for (j = 0; j < columns; ++j) {
			fscanf(file, "%d", &temp);
			matrix->matrix[i][j] = temp;
		}
	}

	fclose(file);

	return matrix;
}

void writeMatrix(char *fileName, Matrix matrix) {
    FILE *file = fopen(fileName, "w+");
	int i, j;
	if ( file == NULL ) {
		printf("Could not write to file: %s\n", fileName);
		exit(1);
	}
    
    fprintf(file, "LINHAS = %d\n", matrix.lines);
    fprintf(file, "COLUNAS = %d\n", matrix.columns);

    for (i = 0; i < matrix.lines; ++i) {
		for (j = 0; j < matrix.columns; ++j) {
			fprintf(file, "%d ", matrix.matrix[i][j]);
		}
        fprintf(file, "\n");
	}
    
    fclose(file);
}

int matrixAreEqual(Matrix matrix1, Matrix matrix2){
	if(	matrix1.lines == matrix2.lines && 
		matrix2.columns == matrix2.columns) {
		int i, j;
		for (i = 0; i < matrix1.lines; ++i) {
			for (j = 0; j < matrix1.columns; ++j) {
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
	for(i = 0; i < matrix.lines; ++i){
		for(j = 0; j < matrix.columns; ++j){
			printf("%d ", matrix.matrix[i][j]);
		}
		printf("\n");
	}
}

#endif
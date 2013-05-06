#include "stdio.h"
#include "../lib/matrix.c"
#include "../lib/test.c"

void shouldReadMatrixSize(){
	Matrix *matrix = readMatrix("test_files/matrix_2_2.txt");
	
	assertThat(matrix->lines, 2, "shouldReadMatrixSize - lines");
	assertThat(matrix->columns, 2, "shouldReadMatrixSize - columns");
}

void shouldReadMatrixTwoByTwo(){
	Matrix *result = readMatrix("test_files/matrix_2_2.txt");

	Matrix expectedMatrix;
	expectedMatrix.lines = expectedMatrix.columns = 2;
	allocMatrix(&expectedMatrix);
	setMatrixItem(&expectedMatrix, 0, 0, 17); setMatrixItem(&expectedMatrix, 0, 1, 8);
	setMatrixItem(&expectedMatrix, 1, 0, 4);  setMatrixItem(&expectedMatrix, 1, 1, 23);

	assertThatMatrixAreEqual(*result, expectedMatrix, "shouldReadMatrixTwoByTwo");
}

int main() {
	shouldReadMatrixSize();
	shouldReadMatrixTwoByTwo();
	return 0;
}
#include "stdio.h"
#include "../lib/matrix.c"
#include "../lib/test.c"

Matrix expectedMatrix;

void setup(){
    expectedMatrix.lines = 2;
    expectedMatrix.columns = 3;
    allocMatrix(&expectedMatrix);
    
    setMatrixItem(&expectedMatrix, 0, 0, 1); setMatrixItem(&expectedMatrix, 0, 1, 2); setMatrixItem(&expectedMatrix, 0, 2, 3);
    setMatrixItem(&expectedMatrix, 1, 0, 4); setMatrixItem(&expectedMatrix, 1, 1, 5); setMatrixItem(&expectedMatrix, 1, 2, 6);
}

void shouldWriteMatrix(){
    writeMatrix("matrix_test.txt", expectedMatrix);
    
    Matrix *result = readMatrix("matrix_test.txt");

    assertThatMatrixAreEqual(*result, expectedMatrix, "shouldWriteMatrix");
}

void shouldWriteMatrixHeader(){
    writeMatrix("matrix_test.txt", expectedMatrix);
    
    Matrix *result = readMatrix("matrix_test.txt");
    
    assertThat(result->lines, expectedMatrix.lines, "shouldWriteMatrixHeader - lines");
    assertThat(result->columns, expectedMatrix.columns, "shouldWriteMatrixHeader - columns");
}

void startTests(){
    shouldWriteMatrix();
    shouldWriteMatrixHeader();
}

int main(){
    setup();
    startTests();
    return 0;
}

#include "stdio.h"
#include "../lib/matrix.c"
#include "../lib/test.c"

Matrix expectedMatrix;

void setup(){
    expectedMatrix.lines = 2;
    expectedMatrix.columns = 3;
    allocMatrix(&expectedMatrix);
    
    expectedMatrix.matrix[0][0] = 1; expectedMatrix.matrix[0][1] = 2; expectedMatrix.matrix[0][2] = 3;
    expectedMatrix.matrix[1][0] = 4; expectedMatrix.matrix[1][1] = 5; expectedMatrix.matrix[1][2] = 6;
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

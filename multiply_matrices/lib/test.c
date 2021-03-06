#include "stdio.h"
#include "matrix.c"
#include "string.h"

void assertThatMatrixAreEqual(Matrix actual, Matrix expected, char *message) {
	if ( matrixAreEqual(actual, expected) ) {
		printf("Pass: %s\n", message);
	} else {
		printf("Fail: Matrix are not equal. %s\n", message);
		printf("Expected: \n");
		printMatrix(expected);
		printf("to be equal actual: \n");
		printMatrix(actual);
	}
}

void assertThatMatrixAreNotEqual(Matrix actual, Matrix expected, char *message) {
	if ( matrixAreEqual(actual, expected) ) {
		printf("Fail: %s\n", message);
		printf("Expected: \n");
		printMatrix(expected);
		printf("to be different of actual: \n");
		printMatrix(actual);
	} else {
		printf("Pass: %s\n", message);
	}
}

void assertThat(int actual, int expected, char *message) {
	if ( actual == expected ) {
		printf("Pass: %s\n", message);	
	} else {
		printf("Fail: %s\n", message);
		printf("Expected: %d\n", expected);
		printf("Actual: %d\n", actual);
	}
}

void assertThatString(char *actual, char *expected, char *message) {
	if (strcmp(actual, expected) == 0) {
		printf("Pass: %s\n", message);			
	} else {
		printf("Fail: %s\n", message);
		printf("Expected: %s\n", expected);
		printf("Actual: %s\n", actual);
	}
}
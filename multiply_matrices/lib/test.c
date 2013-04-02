void assertThatMatrixAreEqual(Matrix actual, Matrix expected, char *message) {
	if ( matrixAreEqual(actual, expected) ) {
		printf("Pass: %s\n", message);
	} else {
		printf("Fail: Matrix are not equal.\n");
		printf("Expected: \n");
		printMatrix(expected);
		printf("Expected: \n");
		printMatrix(actual);
	}
}

void assertThatMatrixAreNotEqual(Matrix actual, Matrix expected, char *message) {
	if ( matrixAreEqual(actual, expected) ) {
		printf("Fail: %s\n", message);
		printf("Expected: \n");
		printMatrix(expected);
		printf("Expected: \n");
		printMatrix(actual);
	} else {
		printf("Pass: %s\n", message);
	}
}
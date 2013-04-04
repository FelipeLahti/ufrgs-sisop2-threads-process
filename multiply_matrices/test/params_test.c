#include "../lib/test.c"
#include "../lib/params.c"


void shouldGetNumberOfProcessOrThreads() {
	int argc = 2;
	char const *argv[] = {
		"programName.out",
		"15"
	};
	int result = getNumberOfProcessOrThreadNumber(argc, argv);
	int expectedNumberOfProcessOrThread = 15;
	assertThat(result, expectedNumberOfProcessOrThread, "shouldGetNumberOfProcessOrThreads");
}

void shouldGetDefaultFirstFileMatrixName() {
	int argc = 2;
	char const *argv[] = {
		"programName.out",
		"15"
	};
	char *result = getFileMatrixName(argc, argv, 1);
	char *expectMatrixName = "in1.txt";
	assertThatString(result, expectMatrixName, "shouldGetDefaultFirstFileMatrixName");
}

void shouldGetDefaultSecondFileMatrixName() {
	int argc = 2;
	char const *argv[] = {
		"programName.out",
		"15"
	};
	char *result = getFileMatrixName(argc, argv, 2);
	char *expectMatrixName = "in2.txt";
	assertThatString(result, expectMatrixName, "shouldGetDefaultSecondFileMatrixName");
}

void shouldGetCustomFirstFileMatrixName() {
	int argc = 3;
	char const *argv[] = {
		"programName.out",
		"15",
		"matrix1.txt"
	};
	char *result = getFileMatrixName(argc, argv, 1);
	char *expectMatrixName = "matrix1.txt";
	assertThatString(result, expectMatrixName, "shouldGetCustomFirstFileMatrixName");
}

void shouldGetCustomSecondFileMatrixName() {
	int argc = 4;
	char const *argv[] = {
		"programName.out",
		"15",
		"matrix1.txt",
		"matrix2.txt"
	};
	char *result = getFileMatrixName(argc, argv, 2);
	char *expectMatrixName = "matrix2.txt";
	assertThatString(result, expectMatrixName, "shouldGetCustomSecondFileMatrixName");
}

int	main() {
	shouldGetNumberOfProcessOrThreads();
	shouldGetDefaultFirstFileMatrixName();
	shouldGetDefaultSecondFileMatrixName();
	shouldGetCustomFirstFileMatrixName();
	shouldGetCustomSecondFileMatrixName();
	return 0;
}
#include "../lib/matrix.c"
#include "../lib/test.c"

void shouldSameMatrixBeEqual(){
	Matrix m1;
	m1.lines = m1.columns = 2;
	allocMatrix(&m1);
    setMatrixItem(&m1, 1, 1, 5);

	Matrix m2;
	m2.lines = m2.columns = 2;	
	allocMatrix(&m2);
	setMatrixItem(&m2, 1, 1, 5);

	assertThatMatrixAreEqual(m1, m2, "shouldTwoMatrixBeEqual");
}

void shouldDifferentMatrixNotBeEqual(){
	Matrix m1;
	m1.lines = m1.columns = 2;
	allocMatrix(&m1);
	setMatrixItem(&m1, 1, 1, 5);

	Matrix m2;
	m2.lines = m2.columns = 2;	
	allocMatrix(&m2);
    setMatrixItem(&m2, 1, 1, 4);

	assertThatMatrixAreNotEqual(m1, m2, "shouldDifferentMatrixNotBeEqual");
}

void shouldOneMatrixEqualToItself(){
	Matrix m1;
	m1.lines = m1.columns = 2;
	allocMatrix(&m1);

	assertThatMatrixAreEqual(m1, m1, "shouldAssertThatTwoMatrixAreEqual");
}

void startTests(){
	shouldOneMatrixEqualToItself();
	shouldDifferentMatrixNotBeEqual();
	shouldSameMatrixBeEqual();
}

int main() {
	startTests();
	exit(0);
}
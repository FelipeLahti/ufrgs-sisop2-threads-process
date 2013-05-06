void shouldMultipleLineByColumnInAQuadraticMatrix(){
	Matrix m1; 
	m1.lines = m1.columns = 2;
	allocMatrix(&m1);
    setMatrixItem(&m1, 0, 0, 2); setMatrixItem(&m1, 0, 1, 3);
    setMatrixItem(&m1, 1, 0, 4); setMatrixItem(&m1, 1, 1, 5);

	assertThat(multiplyLineColumn(0,0,m1,m1), 16, "shouldMultipleLineByColumnInAQuadraticMatrix");
	assertThat(multiplyLineColumn(0,1,m1,m1), 21, "shouldMultipleLineByColumnInAQuadraticMatrix");
	assertThat(multiplyLineColumn(1,0,m1,m1), 28, "shouldMultipleLineByColumnInAQuadraticMatrix");
	assertThat(multiplyLineColumn(1,1,m1,m1), 37, "shouldMultipleLineByColumnInAQuadraticMatrix");
}

void shouldMultipleLineByColumnWithColumnLonger(){
	Matrix m1; 
	m1.lines = 2; m1.columns = 1;
	allocMatrix(&m1);
    setMatrixItem(&m1, 0, 0, 2); setMatrixItem(&m1, 0, 1, 4);

	Matrix m2; 
	m2.lines = 1; m2.columns = 2;
	allocMatrix(&m2);
    setMatrixItem(&m2, 0, 0, 3);
    setMatrixItem(&m2, 1, 0, 5);

	int result = multiplyLineColumn(0,0,m1,m2);
	int expected = 26;
	assertThat(result, expected, "shouldMultipleLineByColumnWithColumnLonger");
}

void shouldMultipleLineByColumnSimple(){
	Matrix m1; 
	m1.lines = m1.columns = 2;
	allocMatrix(&m1);
    setMatrixItem(&m1, 0, 0, 2);

	int result = multiplyLineColumn(0,0,m1,m1);
	int expected = 4;
	assertThat(result, expected, "shouldMultipleLineByColumnSimple");
}

void shouldMultipleMatrixTwoByTwo() {
	Matrix m1; 
	m1.lines = m1.columns = 2;
	allocMatrix(&m1);
    setMatrixItem(&m1, 0, 0, 2); setMatrixItem(&m1, 0, 1, 3);
    setMatrixItem(&m1, 1, 0, 4); setMatrixItem(&m1, 1, 1, 5);

	Matrix result = multipleMatrix(m1, m1);

	Matrix expected; 
	expected.lines = expected.columns = 2;
	allocMatrix(&expected);
    setMatrixItem(&expected, 0, 0, 16); setMatrixItem(&expected, 0, 1, 21);
    setMatrixItem(&expected, 1, 0, 28); setMatrixItem(&expected, 1, 1, 37);

	assertThatMatrixAreEqual(expected, result, "shouldMultipleMatrixTwoByTwo");
}

int main(){
	shouldMultipleMatrixTwoByTwo();
	shouldMultipleLineByColumnSimple();
	shouldMultipleLineByColumnWithColumnLonger();
	shouldMultipleLineByColumnInAQuadraticMatrix();
	return 0;
}
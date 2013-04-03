void shouldMultipleLineByColumnInAQuadraticMatrix(){
	Matrix m1; 
	m1.width = m1.height = 2;
	allocMatrix(&m1);
	m1.matrix[0][0] = 2; m1.matrix[0][1] = 3;
	m1.matrix[1][0] = 4; m1.matrix[1][1] = 5;

	assertThat(multiplyLineColumn(0,0,m1,m1), 16, "shouldMultipleLineByColumnInAQuadraticMatrix");
	assertThat(multiplyLineColumn(0,1,m1,m1), 21, "shouldMultipleLineByColumnInAQuadraticMatrix");
	assertThat(multiplyLineColumn(1,0,m1,m1), 28, "shouldMultipleLineByColumnInAQuadraticMatrix");
	assertThat(multiplyLineColumn(1,1,m1,m1), 37, "shouldMultipleLineByColumnInAQuadraticMatrix");
}

void shouldMultipleLineByColumnWithColumnLonger(){
	Matrix m1; 
	m1.width = 2; m1.height = 1;
	allocMatrix(&m1);
	m1.matrix[0][0] = 2; m1.matrix[0][1] = 4;

	Matrix m2; 
	m2.width = 1; m2.height = 2;
	allocMatrix(&m2);
	m2.matrix[0][0] = 3; 
	m2.matrix[1][0] = 5;

	int result = multiplyLineColumn(0,0,m1,m2);
	int expected = 26;
	assertThat(result, expected, "shouldMultipleLineByColumnWithColumnLonger");
}

void shouldMultipleLineByColumnSimple(){
	Matrix m1; 
	m1.width = m1.height = 2;
	allocMatrix(&m1);
	m1.matrix[0][0] = 2;
	int result = multiplyLineColumn(0,0,m1,m1);
	int expected = 4;
	assertThat(result, expected, "shouldMultipleLineByColumnSimple");
}

void shouldMultipleMatrixTwoByTwo() {
	Matrix m1; 
	m1.width = m1.height = 2;
	allocMatrix(&m1);
	m1.matrix[0][0] = 2; m1.matrix[0][1] = 3;
	m1.matrix[1][0] = 4; m1.matrix[1][1] = 5;

	Matrix result = multipleMatrix(m1, m1);

	Matrix expected; 
	expected.width = expected.height = 2;
	allocMatrix(&expected);
	expected.matrix[0][0] = 16; expected.matrix[0][1] = 21;
	expected.matrix[1][0] = 28; expected.matrix[1][1] = 37;

	assertThatMatrixAreEqual(expected, result, "shouldMultipleMatrixTwoByTwo");
}

int main(){
	shouldMultipleMatrixTwoByTwo();
	shouldMultipleLineByColumnSimple();
	shouldMultipleLineByColumnWithColumnLonger();
	shouldMultipleLineByColumnInAQuadraticMatrix();
	return 0;
}
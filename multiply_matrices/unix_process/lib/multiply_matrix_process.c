#include <unistd.h>

Matrix *sharedMatrix;

Matrix multipleMatrix(Matrix m1, Matrix m2){
	Matrix result;
	result.width = m1.width;
	result.height = m2.height;
	allocMatrix(&result);

	sharedMatrix = &result;

	pid_t *process = calloc(result.width * result.height, sizeof(pid_t));
	int status;

	int i,j;
	for (i = 0; i < result.width; ++i) {
		for (j = 0; j < result.height; ++j) {
			pid_t id = process[i * result.width + j] = fork();			
			if ( id == 0) {
				result.matrix[i][j] = multiplyLineColumn(i, j, m1, m2);
				printf("%d\n", result.matrix[i][j]);
				exit(0);
			} else {
				//printf("%d\n", id);
				//sleep(1);
			}
		}
	}

	for (i = 0; i < result.width * result.height; ++i) {
		wait(&process[i]);
	}

	return result;
}
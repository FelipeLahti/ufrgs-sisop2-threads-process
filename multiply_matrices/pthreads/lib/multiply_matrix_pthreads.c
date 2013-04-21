#include <pthread.h>
#include <stdlib.h>
#define DEFAULT_THREADS_NUMBER 3

typedef struct {
    Matrix *m1;
    Matrix *m2;
    Matrix *result;
    int threadId;
    int numberOfThreads;
} Args;

void *childProcess(void *arg) {
    Args *args = (Args *) arg;
    int i, j;

    for(i = args->threadId; i < args->result->lines; i+=args->numberOfThreads){
        for(j = 0; j < args->result->columns; j++){
            args->result->matrix[i][j] = multiplyLineColumn(i, j, *args->m1, *args->m2);
        }
    }
    
    pthread_exit(NULL);
}

Matrix multiplyMatrixUsingPthreads(Matrix m1, Matrix m2, int numberOfThreads) {
    Matrix result = prepareMatrixMultiplicationResult(m1,m2);

    pthread_t *threads = calloc(numberOfThreads, sizeof(pthread_t));
    
    int i;
    for (i = 0; i < numberOfThreads; i++) {
        Args *args = calloc(1, sizeof(Args));
        args->result = &result;
        args->m1 = &m1;
        args->m2 = &m2;
        args->numberOfThreads = numberOfThreads;
        args->threadId = i;
        
        pthread_create(&threads[i], NULL, childProcess, args);
    }

    for (i = 0; i < numberOfThreads; ++i) {
        pthread_t th = threads[i];
        pthread_join(th, NULL);
    }
    
	return result;
}

Matrix multipleMatrix(Matrix m1, Matrix m2){
    return multiplyMatrixUsingPthreads(m1, m2, DEFAULT_THREADS_NUMBER);
}
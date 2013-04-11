#include <pthread.h>
#include <stdlib.h>
#define DEFAULT_THREADS_NUMBER 3

typedef struct {
    int line;
    int column;
} Position;

typedef struct {
    Matrix *result;
    Matrix *m1;
    Matrix *m2;
    Position *position;
}Args;


void setPosition(Position *position, int line, int column){
    position->line = line;
    position->column = column;
}

Position nextPosition(Args *args){
    Position pos;
    //lock
    int maxLines = args->result->lines;
    int maxColumns = args->result->columns;
    
    if(args->position->column < maxColumns - 1){
        pos.line = args->position->line;
        args->position->column++;
        pos.column = args->position->column;
    } else if (args->position->line < maxLines - 1){
        args->position->line++;
        args->position->column = 0;
        pos.line = args->position->line;
        pos.column = args->position->column;
    }
    else {
        pos.column = pos.line = -1;
    }
    //unlock
    return pos;
}

int hasNextPosition(Position position){
    return position.line == -1 && position.column == -1 ? 0 : 1;
}

void *childPartialResultProcess(void *arg) {
    Args *args = (Args *) arg;
    
    Position posToCalculate = nextPosition(args);
    while(hasNextPosition(posToCalculate)){
        args->result->matrix[posToCalculate.line][posToCalculate.column] = multiplyLineColumn(posToCalculate.line, posToCalculate.column, *args->m1, *args->m2);
        posToCalculate = nextPosition(args);
    }
    return 0;
}

Matrix multiplyMatrixUsingPthreads(Matrix m1, Matrix m2, int threadsNumber) {
    Matrix result = prepareMatrixMultiplicationResult(m1,m2);

    pthread_t *threads = calloc(threadsNumber, sizeof(pthread_t));
    Args args;
    args.result = &result;
    args.m1 = &m1;
    args.m2 = &m2;
    args.position = calloc(1, sizeof(Position));
    setPosition(args.position, 0, -1);

    int i;
    for (i = 0; i < threadsNumber; ++i) {
        pthread_create(&threads[i], NULL, childPartialResultProcess, &args);
    }

    for (i = 0; i < threadsNumber; ++i) {
        pthread_t th = threads[i];
        pthread_join(th, NULL);
    }
    
	return result;
}

Matrix multipleMatrix(Matrix m1, Matrix m2){
    return multiplyMatrixUsingPthreads(m1, m2, DEFAULT_THREADS_NUMBER);
}
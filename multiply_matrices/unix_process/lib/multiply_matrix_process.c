#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DEFAULT_PROCESS_NUMBER 2

typedef struct {
    Matrix *m1;
    Matrix *m2;
    int* result;
    int processId;
    int numberOfProcess;
} Args;

void childProcess(Args args){
    int i, j;

    for(i= args.processId;i < args.m1->lines; i+= args.numberOfProcess){
        for(j = 0; j < args.m2->columns; j++){
            args.result[i * args.m2->columns + j] = multiplyLineColumn(i, j, *args.m1, *args.m2);
        }
    }
    
	exit(0);
}

Matrix multipleMatrixUsingProcess(Matrix m1, Matrix m2, int numberOfProcess) {

    int i, j;
	Matrix result = prepareMatrixMultiplicationResult(m1,m2);
    
    //Allocating shared memory for process
    int *sharedResult = calloc(result.lines * result.columns, sizeof(int));
    int segmentId;
    segmentId = shmget(IPC_PRIVATE, sizeof(sharedResult), S_IRUSR | S_IWUSR);
    
    if ( segmentId < 0) {
        printf("None shared segment memory available. Check shm opens with cmd 'ipcs' in your terminal.");
        exit(1);
    }
    
    sharedResult = (int *) shmat(segmentId, NULL, 0);
    
	//Dispatching all process
	pid_t *process = calloc(numberOfProcess, sizeof(pid_t));

	for (i = 0; i < numberOfProcess && i < result.lines; ++i)	{
		process[i] = fork();
        Args args;
        args.m1 = &m1;
        args.m2 = &m2;
        args.numberOfProcess = numberOfProcess;
        args.processId = i;
        args.result = sharedResult;

		if (process[i] == 0) {
			childProcess(args);
		}
	}

    //Waiting process to finish calculation
	for (i = 0; i < numberOfProcess && i < result.lines; ++i) {
        pid_t pid = process[i];
        waitpid(pid,0,0);
	}
    
    //Getting results
    for(i = 0; i < result.lines; i++) {
        for(j = 0; j < result.columns; j++){
            setMatrixItem(&result, i, j, sharedResult[i * result.columns + j]);
        }
    }
    
    //Clean up
    shmdt(sharedResult);
    shmctl(segmentId, IPC_RMID, NULL);

	return result;
}

Matrix multipleMatrix(Matrix m1, Matrix m2){
	return multipleMatrixUsingProcess(m1, m2, DEFAULT_PROCESS_NUMBER);
}
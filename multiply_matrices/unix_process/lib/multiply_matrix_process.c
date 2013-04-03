#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>

#define DEFAULT_PROCESS_NUMBER 2

typedef struct {
	long type;
	int result;	
	int line;
	int column;
} LineColumnResult;

typedef struct {
	key_t ipckey;	
	int id;	
} MessageQueue;

MessageQueue inQueue, outQueue;

void initLineColumnResultMessage(LineColumnResult *variable, int line, int column) {
	variable->type = 1;
	variable->result = 0;
	variable->line = line;
	variable->column = column;
}

void initQueue(MessageQueue *queue) {
	queue->ipckey = ftok(".", 'm');
	queue->id = msgget(queue->ipckey, IPC_CREAT | 0666);
}

void printLineColumnResult(LineColumnResult p){
	printf("Line: %d Column: %d Result: %d\n", p.line, p.column, p.result);	
}

void childPartialResultProcess(Matrix m1, Matrix m2){

	while(1) {
		LineColumnResult temp;
		int received = msgrcv(inQueue.id, &temp, sizeof(LineColumnResult), 1, IPC_NOWAIT);

		if (received >= 0){
			temp.result = multiplyLineColumn(temp.line, temp.column, m1, m2);
			temp.type = 2;
			msgsnd(outQueue.id, &temp, sizeof(LineColumnResult), 0);
		} else {
			break;
		}
	}

	exit(0);
}

Matrix multipleMatrixUsingProcess(Matrix m1, Matrix m2, int processNumber) {

	Matrix result = prepareMatrixMultiplicationResult(m1,m2);
	int i,j;
	
	initQueue(&inQueue);
	initQueue(&outQueue);	

	//Sending work to the queue
	for (i = 0; i < result.width; ++i) {
		for (j = 0; j < result.height; ++j) {
			LineColumnResult lineColumnResult;
			initLineColumnResultMessage(&lineColumnResult, i, j);
			msgsnd(inQueue.id, &lineColumnResult, sizeof(LineColumnResult), 0);
		}
	}

	//Dispatching process
	pid_t *process = calloc(processNumber, sizeof(pid_t));

	for (i = 0; i < processNumber; ++i)	{
		process[i] = fork();

		if (process[i] == 0) {
			childPartialResultProcess(m1, m2);
		}
	}

	//Grouping results from each process
	int totalCalls = result.width * result.height;

	while(1) {
		LineColumnResult partialResult;
		int received = msgrcv(outQueue.id, &partialResult, sizeof(LineColumnResult), 2, IPC_NOWAIT);
		if (received >= 0) {			
			result.matrix[partialResult.line][partialResult.column] = partialResult.result;
			totalCalls--;
		} else {
			if(totalCalls <= 0) {
				break;
			}
		}
	}

	for (i = 0; i < processNumber; ++i) {
		wait(&process[i]);
	}

	return result;
}

Matrix multipleMatrix(Matrix m1, Matrix m2){
	return multipleMatrixUsingProcess(m1, m2, DEFAULT_PROCESS_NUMBER);
}
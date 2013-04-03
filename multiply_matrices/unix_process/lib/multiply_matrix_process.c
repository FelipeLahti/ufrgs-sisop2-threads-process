#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>

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

#define TOTAL_PROCESS 2

void init_line_column(LineColumnResult *variable, int line, int column) {
	variable->type = 1;
	variable->result = 0;
	variable->line = line;
	variable->column = column;
}

void printLineColumn(LineColumnResult p){
	printf("Line: %d Column: %d Result: %d\n", p.line, p.column, p.result);	
}

void childProcess(Matrix m1, Matrix m2){

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

Matrix prepareResultMatrix(Matrix m1, Matrix m2) {
	Matrix result;
	result.width = m1.width;
	result.height = m2.height;
	allocMatrix(&result);
	return result;
}

void initQueue(MessageQueue *queue) {
	queue->ipckey = ftok(".", 'm');
	queue->id = msgget(queue->ipckey, IPC_CREAT | 0666);
}

Matrix multipleMatrix(Matrix m1, Matrix m2){
	Matrix result = prepareResultMatrix(m1,m2);
	int i,j;
	
	initQueue(&inQueue);
	initQueue(&outQueue);	

	for (i = 0; i < result.width; ++i) {
		for (j = 0; j < result.height; ++j) {
			LineColumnResult lineColumnResult;
			init_line_column(&lineColumnResult, i, j);

			msgsnd(inQueue.id, &lineColumnResult, sizeof(LineColumnResult), 0);
		}
	}

	//Dispatching process
	pid_t *process = calloc(TOTAL_PROCESS, sizeof(pid_t));

	for (i = 0; i < TOTAL_PROCESS; ++i)	{
		process[i] = fork();

		if (process[i] == 0) {
			printf("Process created!\n");
			childProcess(m1, m2);
		}
	}

	int totalCalls = result.width * result.height;

	while(1) {
		LineColumnResult temp2;
		int received = msgrcv(outQueue.id, &temp2, sizeof(LineColumnResult), 2, IPC_NOWAIT);
		if (received >= 0){			
			printLineColumn(temp2);
			result.matrix[temp2.line][temp2.column] = temp2.result;
			totalCalls--;
		} else {
			if(totalCalls <= 0) {
				break;
			}
		}
	}

	for (i = 0; i < TOTAL_PROCESS; ++i) {
		wait(&process[i]);
	}

	return result;
}
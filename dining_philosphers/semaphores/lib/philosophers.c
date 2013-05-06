#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define THINKING 1
#define EATING 2
#define HUNGRY 3

sem_t Printing; 
sem_t Room;
sem_t *Fork;
int state[5];
void changeStateAndPrint (int philosopherNumber, char newState){
		
	int i;
	state[philosopherNumber] = newState;
	printf("this is :%d", philosopherNumber);
	for (i=0;i<5;i++){
		if (state[i] == EATING )
			printf("E ");
		if (state[i] == HUNGRY )
			printf("H ");	
		if (state[i] == THINKING )
			printf("T ");	
	}
	printf("\n");
	sem_post(&Printing);
}
void *philosopherThread(void *ptr) {
    int philosopherNumber = *((int *) ptr);
    int sleepTime;
    while (1) {
	//changeStateAndPrint(philosopherNumber, HUNGRY);
        sem_wait(&Room) ;
        sem_wait(&Fork[philosopherNumber]) ;
        sem_wait(&Fork[(philosopherNumber+1) % 5]) ; //for now, its fixed
	printf("%d started eating\n",philosopherNumber);
	//changeStateAndPrint(philosopherNumber, EATING);
	sleepTime = rand() % 10 + 1;
	sleep(sleepTime);
        sem_post(&Fork[philosopherNumber]) ;
        sem_post(&Fork[(philosopherNumber+1) % 5]) ; //also change here
        sem_post(&Room) ;
	printf("%d finished eating\n",philosopherNumber);
    	//changeStateAndPrint(philosopherNumber, THINKING);
    }
    pthread_exit(0);
}

void philosophersUsingSemaphores( int numberOfThreads) {
    pthread_t *threads = calloc(numberOfThreads, sizeof(char));
    Fork = calloc(numberOfThreads,sizeof(sem_t));
    //state = calloc(numberOfThreads,sizeof(char));
    int i, argsAux[5];
    sem_init(&Room, 0, 4);
    sem_init(&Printing, 0, 1);
    for(i=0;i<5;i++) {
        sem_init(&Fork[i], 0, 1);    
    }   
    for (i = 0; i < numberOfThreads; i++) {
	state[i] = THINKING;
    }
    for (i = 0; i < numberOfThreads; i++) {
	argsAux[i] = i;        
        pthread_create(&threads[i], NULL, philosopherThread, (void *) &argsAux[i]);
    }
	
    for(i=0;i<5;i++) {
        pthread_join(threads[i], NULL);
    }

}


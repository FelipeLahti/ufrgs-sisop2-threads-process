#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define THINKING 1
#define EATING 2
#define HUNGRY 3

sem_t Printing; 
sem_t Room;
sem_t *Fork;
int *state;
int philosophers;
void changeStateAndPrint (int philosopherNumber, char newState){
		
	int i;
	sem_wait(&Printing);
	state[philosopherNumber] = newState;
	//printf("this is :%d", philosopherNumber);
	for (i=0;i<philosophers;i++){
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
	sleepTime = rand() % 10 + 1;
	sleep(sleepTime);
	changeStateAndPrint(philosopherNumber, HUNGRY);
        sem_wait(&Room) ;
        sem_wait(&Fork[philosopherNumber]) ;
        sem_wait(&Fork[(philosopherNumber+1) % philosophers]) ; //for now, its fixed
	//printf("%d started eating\n",philosopherNumber);
	changeStateAndPrint(philosopherNumber, EATING);
	sleepTime = rand() % 10 + 1;
	sleep(sleepTime);
	//printf("%d finished eating\n",philosopherNumber);
        sem_post(&Fork[philosopherNumber]) ;
        sem_post(&Fork[(philosopherNumber+1) % philosophers]) ; //also change here
        sem_post(&Room) ;
    	changeStateAndPrint(philosopherNumber, THINKING);
    }
    pthread_exit(0);
}

void philosophersUsingSemaphores( int numberOfThreads) {
    philosophers = numberOfThreads;
    pthread_t *threads = calloc(philosophers, sizeof(sizeof(pthread_t)));
    Fork = calloc(philosophers,sizeof(sem_t));
    state = calloc(philosophers,sizeof(int));
    int i, *argsAux;
    argsAux = calloc(philosophers,sizeof(int));
    sem_init(&Room, 0, philosophers -1);
    sem_init(&Printing, 0, 1);
    for(i=0;i<philosophers;i++) {
        sem_init(&Fork[i], 0, 1);    
    }   
    for (i = 0; i < philosophers; i++) {
	state[i] = THINKING;
    }
    for (i = 0; i < philosophers; i++) {
	argsAux[i] = i;        
        pthread_create(&threads[i], NULL, philosopherThread, (void *) &argsAux[i]);
    }
	
    for(i=0;i<philosophers;i++) {
        pthread_join(threads[i], NULL);
    }

}

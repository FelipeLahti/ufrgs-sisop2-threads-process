#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define THINKING 1
#define EATING 2
#define HUNGRY 3

sem_t *Fork;
sem_t Mutex;
sem_t Printing; 
int *state;
int philosophers;

void changeStateAndPrint (int philosopherNumber, int newState){
		
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

void test(int i) {
	sem_wait(&Mutex);
	if ((state[(i + 4) % philosophers] !=EATING) && (state[i] ==HUNGRY) && (state[(i + 1) % philosophers] !=EATING)) {
		changeStateAndPrint(i,EATING);
		sem_post(&Fork[i]);
	}
	sem_post(&Mutex);
}


void pickup(int i) {
	sem_wait(&Mutex);
	changeStateAndPrint(i,HUNGRY);
	test(i);
	if (state [i] != EATING){ sem_wait(&Fork[i]) ; }
	sem_post(&Mutex);		
}
void putdown(int i) {
	sem_wait(&Mutex);
	changeStateAndPrint(i,THINKING);
	test((i + philosophers - 1) % philosophers);
	test((i + 1) % philosophers);
	sem_post(&Mutex);
}
void *philosopherThread(void *ptr) {
    int philosopherNumber = *((int *) ptr);
    int sleepTime;
    while (1) {
        pickup(philosopherNumber);
	sleepTime = rand() % 10 + 1;
	sleep(sleepTime);
	putdown(philosopherNumber);
	sleepTime = rand() % 10 + 1;
	sleep(sleepTime);
	//printf("%d finished eating\n",philosopherNumber);
     	
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
    sem_init(&Printing, 0, 1);
    sem_init(&Mutex, 0, 1);
    for(i=0;i<philosophers;i++) {
        sem_init(&Fork[i], 0, 1);
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

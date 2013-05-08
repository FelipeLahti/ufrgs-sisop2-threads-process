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
    char *msg = calloc(philosophers * 2, sizeof(char));

    for(i = 0; i < philosophers; i++){
        if (state[i] == EATING)   msg[i] = 'E';
        if (state[i] == HUNGRY)   msg[i] = 'H';
        if (state[i] == THINKING) msg[i] = 'T';
        msg[i+1] = ' ';
    }
    printf("%s\n", msg);

    sem_post(&Printing);
}

void randomSleep(){
    int sleepTime;
    sleepTime = rand() % 10 + 1;
    sleep(sleepTime);
}

void *philosopherThread(void *ptr) {
    int philosopherNumber = *((int *) ptr);

    while (1) {
        randomSleep();
        changeStateAndPrint(philosopherNumber, HUNGRY);

        sem_wait(&Room) ;
        sem_wait(&Fork[philosopherNumber]) ;
        sem_wait(&Fork[(philosopherNumber+1) % philosophers]) ; //for now, its fixed

    	changeStateAndPrint(philosopherNumber, EATING);

        randomSleep();
	changeStateAndPrint(philosopherNumber, THINKING);
        sem_post(&Fork[philosopherNumber]) ;
        sem_post(&Fork[(philosopherNumber+1) % philosophers]) ; //also change here
        sem_post(&Room) ;

    }
    pthread_exit(0);
}

void philosophersUsingSemaphores( int numberOfThreads) {
    int i, *argsAux;
    philosophers = numberOfThreads;
    pthread_t *threads = calloc(philosophers, sizeof(sizeof(pthread_t)));
    Fork = calloc(philosophers,sizeof(sem_t));
    state = calloc(philosophers,sizeof(int));
    argsAux = calloc(philosophers,sizeof(int));

    sem_init(&Room, 0, philosophers -1);
    sem_init(&Printing, 0, 1);

    for(i = 0; i < philosophers; i++) {
        sem_init(&Fork[i], 0, 1);
    }

    for (i = 0; i < philosophers; i++) {
	   state[i] = THINKING;
    }

    for (i = 0; i < philosophers; i++) {
        argsAux[i] = i;
        pthread_create(&threads[i], NULL, philosopherThread, (void *) &argsAux[i]);
    }

    for(i = 0; i < philosophers; i++) {
        pthread_join(threads[i], NULL);
    }
}

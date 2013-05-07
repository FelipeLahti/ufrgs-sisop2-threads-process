#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define THINKING 1
#define EATING 2
#define HUNGRY 3

pthread_mutex_t printing;
pthread_mutex_t m;
pthread_cond_t *cond_state;
int *state;
int philosophers;
int *right_hungry;
int *left_hungry; //this is to avoid starvation

void changeStateAndPrint (int philosopherNumber, int newState){
	//pthread_mutex_lock(&printing);	
	int i;
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
	//pthread_mutex_unlock(&printing);	
	//printf("aaa\nss");
}

void test(int i) {
	//printf("test %d \n", i);
	//printf("passou test%d \n", i);
	if ((state[(i + philosophers - 1) % philosophers] !=EATING) && (state[i] ==HUNGRY) && (state[(i + 1) % philosophers] !=EATING) && !right_hungry[i] && !left_hungry[i] ) {
		changeStateAndPrint(i,EATING);
		pthread_cond_signal(&cond_state[i]);
	}
	
}


void pickup(int i) {
	pthread_mutex_lock(&m);
	//printf("pickup%d \n", i);
	changeStateAndPrint(i,HUNGRY);
	test(i);
	if (state [i] != EATING) pthread_cond_wait(&cond_state[i], &m); 
	right_hungry[(i + 1) % philosophers] = 0;
        left_hungry[(i + philosophers - 1) % philosophers] = 0;	
	pthread_mutex_unlock(&m);			
}
void putdown(int i) {
	pthread_mutex_lock(&m);
	changeStateAndPrint(i,THINKING);
	test((i + philosophers - 1) % philosophers);
	if (state[(i + philosophers - 1) % philosophers] == HUNGRY)
		left_hungry[i] = 1;
	test((i + 1) % philosophers);
	if (state[(i + 1) % philosophers])
		right_hungry[i] = 1;
	pthread_mutex_unlock(&m);
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
    cond_state = calloc(philosophers,sizeof(pthread_cond_t));
    state = calloc(philosophers,sizeof(int));
    left_hungry = calloc(philosophers,sizeof(int));
    right_hungry = calloc(philosophers,sizeof(int));
    int i, *argsAux;
    pthread_mutex_init(&m, NULL);
    pthread_mutex_init(&printing, NULL);
    for(i=0;i<philosophers;i++) {
	left_hungry[i] = 0;
	right_hungry[i] = 0;
	pthread_cond_init(&cond_state[i], NULL);
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

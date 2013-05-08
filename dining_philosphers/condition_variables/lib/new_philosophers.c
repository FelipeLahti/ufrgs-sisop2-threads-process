#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define THINKING 1
#define EATING 2
#define HUNGRY 3

pthread_mutex_t m;
pthread_cond_t *cond_state;
int *state;
int philosophers;
int *right_hungry;
int *left_hungry; //this is to avoid starvation
//o algoritmo usado foi o que esta no livro do silberchatz http://www.google.de/url?sa=t&rct=j&q=operating%20system%20concepts%20pdf&source=web&cd=1&ved=0CDMQFjAA&url=http%3A%2F%2Fiit.qau.edu.pk%2Fbooks%2FOS_8th_Edition.pdf&ei=1T2IUY7YJe-w4APr94HYAQ&usg=AFQjCNHJuAZTm-YxdmXzTEW5jwNLk7Rbdw&cad=rja

//url acima se tu qusier dar uma olhada, tem na definicao do trabalho aonde olhar
void changeStateAndPrint (int philosopherNumber, int newState){	//gambiarra pra setar um estado e imprimir todos os filosofos
	int i;
	state[philosopherNumber] = newState;
	for (i=0;i<philosophers;i++){
		if (state[i] == EATING )
			printf("E ");
		if (state[i] == HUNGRY )
			printf("H ");	
		if (state[i] == THINKING )
			printf("T ");	
	}
	printf("\n");
}

void test(int i) { // como test sempre e chamado por pickup ou putdown, que ja estao no mutex, nao precisamos mutex aqui...
	if ((state[(i + philosophers - 1) % philosophers] !=EATING) && (state[i] ==HUNGRY) && (state[(i + 1) % philosophers] !=EATING) && !right_hungry[i] && !left_hungry[i] ) {
		changeStateAndPrint(i,EATING);
		pthread_cond_signal(&cond_state[i]);
	}
	
}


void pickup(int i) { //o deadlock e evitado pois o filosofo pega os dois talheres de forma exclusiva
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
	//if (state[(i + philosophers - 1) % philosophers] == HUNGRY)
	//	left_hungry[i] = 1; //serve para evitar a starvation, ou seja, se quando devolvemos o talher, o vizinho quer comer, damos a prioridade pra ele, pra evitar que alguem fique comendo como um gordo indefinidamente e cometa starvation
	test((i + 1) % philosophers);
	//if (state[(i + 1) % philosophers])
	//	right_hungry[i] = 1;
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
     	
    }
    pthread_exit(0);
}

void philosophersUsingSemaphores( int numberOfThreads) {
    philosophers = numberOfThreads;
    pthread_t *threads = calloc(numberOfThreads, sizeof(sizeof(pthread_t)));
    cond_state = calloc(numberOfThreads,sizeof(pthread_cond_t)); //variaveis de condicao
    state = calloc(numberOfThreads,sizeof(int));
    left_hungry = calloc(numberOfThreads,sizeof(int)); //para starvation
    right_hungry = calloc(numberOfThreads,sizeof(int));
    int i, *argsAux;
    pthread_mutex_init(&m, NULL); //mutex para simular monitor
    for(i=0;i<numberOfThreads;i++) {
	left_hungry[i] = 0;
	right_hungry[i] = 0;
	pthread_cond_init(&cond_state[i], NULL);  //inicializa conditions variables, e todos estao pensando
	state[i] = THINKING;    
    }   
    for (i = 0; i < numberOfThreads; i++) {
	argsAux[i] = i;        
        pthread_create(&threads[i], NULL, philosopherThread, (void *) &argsAux[i]); //cria philosphers threads
    }
	
    for(i=0;i<numberOfThreads;i++) {
        pthread_join(threads[i], NULL);
    }

}

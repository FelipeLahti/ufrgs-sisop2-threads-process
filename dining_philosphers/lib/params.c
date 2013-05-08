#include "stdlib.h"
#include "stdio.h"

int getNumberOfPhilosophers(int argc, char const *argv[]){
	if (argc < 2) {
		printf("You must have to pass the number of philosophers.");
		exit(1);
	}
	return atoi(argv[1]);
}
#include "stdlib.h"
#include "../lib/params.c"
#include "lib/new_philosophers.c"
#include <time.h>

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int philosophers = getNumberOfPhilosophers(argc, argv);
	philosophersUsingSemaphores(philosophers);

	return 0;
}
#include "stdlib.h"
#include "../lib/params.c"
#include "lib/philosophers.c"
#include <time.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int philosophers = getNumberOfPhilosophers(argc, argv);
	philosophersUsingSemaphores(philosophers);

	return 0;
}

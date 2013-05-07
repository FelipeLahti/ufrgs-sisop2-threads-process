#include "stdlib.h"
#include "../lib/matrix.c"
#include "../lib/params.c"
#include "lib/philosophers.c"
#include <time.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int philosophers = getNumberOfProcessOrThreadNumber(argc, argv);
	//int philosophers = 5;	
	philosophersUsingSemaphores(philosophers);
    
	return 0;
}

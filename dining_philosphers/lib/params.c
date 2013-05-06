#include "string.h"

int getNumberOfProcessOrThreadNumber(int argc, char const *argv[]){
	if (argc < 2) {
		printf("You must have to pass the number of process.");
		exit(1);
	} 
	return atoi(argv[1]);
}

char *getFileMatrixName(int argc, char const *argv[], int matrixIndex){
	if (argc < 2 + matrixIndex) {
		char *defaultValue = calloc(256, sizeof(char));
		snprintf(defaultValue, sizeof(defaultValue), "in%d.txt", matrixIndex );
		return defaultValue;
	} 

	char *customFileName = calloc(strlen(argv[1 + matrixIndex])+1, sizeof(char));
	strcpy(customFileName, argv[1 + matrixIndex]);
	return customFileName;
}
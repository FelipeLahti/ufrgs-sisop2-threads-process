int getNumberOfProcessOrThreadNumber(int argc, char const *argv[]){
	int i;
	
	if (argc < 2) {
		printf("You must have to pass the number of process.");
		exit(1);
	} 
	return atoi(argv[1]);
}

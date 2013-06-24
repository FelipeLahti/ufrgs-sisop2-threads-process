//teste
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 4000

typedef struct
{
	char name[256];
	int socket;
	struct USER *next;
} USER;

void *clientFunc (void * arg) {
	char buffer[256];
	int n;
	int sockfd = *(int *) arg;

	bzero(buffer,256);

	/* read from the socket */
	while(1){
		n = read(sockfd, buffer, 256);
		if (n < 0) {
			printf("Disconnect from server\n");
			exit(1);
		}

		printf("%s\n",buffer);
	}
}

void initUser(USER *user){
	printf("Nickname: ");
	fgets(user->name, 256, stdin);
	int len = strlen(user->name);
	if (user->name[len - 1] == '\n')
	    user->name[len - 1] = '\0';

}

void changeName (char * buffer) {

}

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	pthread_t thread;

    char buffer[256];
    if (argc < 2) {
		fprintf(stderr,"usage %s hostname\n", argv[0]);
		exit(0);
    }

	server = gethostbyname(argv[1]);
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("ERROR opening socket\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);


	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        printf("ERROR connecting\n");
	}
    else {
		pthread_create(&thread, NULL, clientFunc, &sockfd);

		USER user;
		initUser(&user);

		strcpy (buffer,"/name ");
		strcat (buffer, user.name);

		write(sockfd, buffer, strlen(buffer));

		while(1) {
			printf("%s: ", user.name);

			bzero(buffer, 256);
			fgets(buffer, 256, stdin);

			/* write in the socket */
			n = write(sockfd, buffer, strlen(buffer));
			if (n < 0)
				printf("ERROR writing to socket\n");

			if (strcmp(buffer, "/exit\n") == 0)
				break;
			//if (strcmp(buffer, "/name\n") == 0)
				//change name
				//break;
			//if (strcmp(buffer, "/check\n") == 0)
				//check people in room
				//break;
		}
		close(sockfd);
	}
    return 0;
}

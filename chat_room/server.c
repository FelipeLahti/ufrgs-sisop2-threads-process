#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


#define PORT 4000

typedef struct
{
	char name[15];
	int socket;
	struct USER *next;
}USER;

void *serverFunc (void * arg) {
	char buffer[256];
	int n;
	int newsockfd = *(int *) arg;
	
	
	while(1) {
		
		bzero(buffer, 256);
		
		/* read from the socket */
		n = read(newsockfd, buffer, 256);
		if (n < 0) 
			printf("ERROR reading from socket");
		
		if (strcmp(buffer, "/exit\n") == 0) {
			//n = write(newsockfd,"You are disconnected\n", 20);
			//if (n < 0) 
			//	printf("ERROR writing to socket");
			printf("User discconected from chat\n\n");
			close(newsockfd);
			pthread_exit(NULL);
		}	
		else {
			printf("Here is the message: %s\n", buffer);	
			/* write in the socket */ 
			n = write(newsockfd,"I got your message", 18);
			if (n < 0) 
				printf("ERROR writing to socket");
		}
	}
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, n;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t thread;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        printf("ERROR opening socket");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(serv_addr.sin_zero), 8);     
    
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		printf("ERROR on binding");
	
	listen(sockfd, 5);
	
	clilen = sizeof(struct sockaddr_in);
	
	while(1) {
			
		if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1) 
			printf("ERROR on accept");
		
		pthread_create(&thread, NULL, serverFunc, &newsockfd);
	}

	close(newsockfd);
	close(sockfd);
	return 0; 
}

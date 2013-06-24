#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 4000

typedef struct {
	char name[256];
	int socket;
	struct USER *next;
} USER;

USER *firstList;
pthread_mutex_t m;

void printUserList(){
	USER *iterator = firstList;
	printf("Printing user list\n");
	while(iterator != 0) {
		printf("User -> %s\n", iterator->name);
		iterator = iterator->next;
	}
}

void addUserToList(USER *user){
	pthread_mutex_lock(&m);
	if (firstList == 0) {
		firstList = user;
		firstList->next = 0;
	} else {
		USER *iterator = firstList;

		while(iterator->next != 0){
			iterator = iterator->next;
		}
		iterator->next = user;
	}
	pthread_mutex_unlock(&m);
}


void removeUser(USER **listP, USER element) {
	pthread_mutex_lock(&m);
	USER *currP, *prevP;
	prevP = NULL;

	for (currP = *listP; currP != NULL; prevP = currP, currP = currP->next) {
		if (currP->socket == element.socket) {
			if (prevP == NULL) {
				*listP = currP->next;
			} else {
				prevP->next = currP->next;
			}
			return;
		}
	}
	pthread_mutex_unlock(&m);
	printUserList();
}

void dispatchMessageUserEnterInRoom(USER *user) {
	//send message to all user
	//dispatchAll("User Fulano entered the room")
	printf("User %s entered the room\n", user->name);
}

void dispatchMessageUserChangedName(USER *user, char *oldName){
	printf("%s changed nickname to %s\n", oldName, user->name);
}

void dispatchUserLeftRoom(USER *user){
	printf("User %s left the room\n", user->name);
	removeUser(&firstList, *user);
	close(user->socket);
	pthread_exit(NULL);
}

void *serverFunc (void * arg) {
	char buffer[256];
	int n;
	int newsockfd = *(int *) arg;

	USER user;
	user.socket = newsockfd;

	while(1) {

		bzero(buffer, 256);

		/* read from the socket */
		n = read(newsockfd, buffer, 256);
		if (n <= 0) {
			dispatchUserLeftRoom(&user);
			break;
		}
		
		if (strcmp(buffer, "/exit\n") == 0) {
			dispatchUserLeftRoom(&user);
		} else if(strstr(buffer, "/name") >= 0) {
			if(strlen(user.name) <= 0) {
				sscanf(buffer, "/name %s", user.name);
				addUserToList(&user);
				dispatchMessageUserEnterInRoom(&user);
			} else {
				char oldName[256];
				strcpy(oldName, user.name);
				sscanf(buffer, "/name %s", user.name);
				dispatchMessageUserChangedName(&user, oldName);
			}
		} else {
			printf("Here is the message: %s\n", buffer);
			n = write(newsockfd,"I got your message", 18);
			if (n < 0) {
				printf("ERROR writing to socket");
			}
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
	pthread_mutex_init(&m, NULL);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("ERROR opening socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(serv_addr.sin_zero), 8);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR on binding port");
		exit(1);
	}

	listen(sockfd, 5);

	clilen = sizeof(struct sockaddr_in);

	while(1) {
		printf("Waiting for connections...\n");
		if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) == -1)
			printf("ERROR on accept");

		printf("Socket id => %d\n", newsockfd);
		pthread_create(&thread, NULL, serverFunc, &newsockfd);
	}

	close(newsockfd);
	close(sockfd);
	return 0;
}

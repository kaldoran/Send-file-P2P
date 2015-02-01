//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "error.h"

#define MAX_CONNEXION 3
#define PORT 42000

int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);

    fd_set rdfs;

    char Rep[80];
    int i, total = 0, n = 0;
    int serveur_socket;

    int max_socket;

    int struct_size;
    int sock_client[MAX_CONNEXION];
    struct sockaddr_in s_serveur;
    struct sockaddr_in s_client; 
    struct_size = sizeof(struct sockaddr_in);
    	
    s_serveur.sin_family = AF_INET;
	s_serveur.sin_addr.s_addr = INADDR_ANY;
	s_serveur.sin_port = htons(PORT);	
	
	if ( (serveur_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		QUIT_MSG("Can't create the socket\n");
	}

	if ( bind(serveur_socket, (struct sockaddr *)&s_serveur, struct_size) == -1){
		QUIT_MSG("Can't bind the socket\n");
	}
	
	/* Hey listen */
	if ( listen(serveur_socket,MAX_CONNEXION) == -1 ){
		QUIT_MSG("Socket listen trouble\n");
	}
	
	max_socket = serveur_socket;
		
	for ( ;; ) {
	
		FD_ZERO(&rdfs);
	
		/* Add the socket f the server */
		FD_SET(serveur_socket, &rdfs);
		
		/* Add socket of each client */
		for(i = 0; i < total; i++) {
		     FD_SET(sock_client[i], &rdfs);
		}
		
		if(select(max_socket + 1, &rdfs, NULL, NULL, NULL) == -1) {
			QUIT_MSG("Can't select\n");
		}
		
		if(FD_ISSET(serveur_socket, &rdfs)) {
			sock_client[total] = accept(serveur_socket, (struct sockaddr*) &s_client, (socklen_t *) &struct_size);
			
			max_socket = ((sock_client[total] > max_socket) ? sock_client[total] : max_socket);
			
			printf("New client [%d]\n", sock_client[total]);
			
			++total;
		}
		else {	/* A client wrote something */	
			for(i = 0; i < total; i++) {
				if(FD_ISSET(sock_client[i], &rdfs)) {
					n = read(sock_client[i], Rep, 80);
				
					printf("[[INFO] Server] (%d): message recu <%s> [Socket : %d]\n", n, Rep, sock_client[i]);
					memset(Rep, ' ', 80);
					FD_CLR(sock_client[i], &rdfs);
				}
			}
		}
	}
	
	for(i = 0; i < total; i++) {
		close(sock_client[i]);
		close(serveur_socket);
	}
	
    printf("[[INFO] Server] Welcome to this awesome new project\n");
    
    exit(EXIT_SUCCESS);
}

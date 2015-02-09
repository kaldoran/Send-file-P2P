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
#include <arpa/inet.h>
#include <signal.h>

#include "error.h"
#include "struct_socket.h"

#define MAX_CONNEXION 1
#define PORT 42000
#define NB_MAX_COLLECTOR 10

int initServerSocket() {
    int struct_size, serveur_socket;
    struct sockaddr_in s_serveur;
    struct_size = sizeof(struct sockaddr_in);
        
    s_serveur.sin_family = AF_INET;
    s_serveur.sin_addr.s_addr = INADDR_ANY;
    s_serveur.sin_port = htons(PORT);    
    
    if ( (serveur_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        QUIT_MSG("Can't create the socket : ");
    }

    if ( bind(serveur_socket, (struct sockaddr *)&s_serveur, struct_size) == -1){
        QUIT_MSG("Can't bind the socket : ");
    }
    
    /* Hey listen */
    if ( listen(serveur_socket,MAX_CONNEXION) == -1 ){
        QUIT_MSG("Socket listen trouble : ");
    }
    
    return serveur_socket;
}

Client *allocClient(int number) {
    Client *client;
    
    if ( (client = calloc(number, sizeof(client))) == NULL ) {
        QUIT_MSG("Can't allocate memory for client");
    }

    return client;
}

int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);
    
    fd_set rdfs;
    int random;
    
    char *ret;
    char inBuf[20];
    Client *client;
    struct sockaddr_in s_client;
    int struct_size = sizeof(struct sockaddr_in);
    int i, j, total = 0;
    
    struct timeval tval;
    int serveur_socket, max_socket;
    
    tval.tv_sec  = 60;
    tval.tv_usec = 0; 

    serveur_socket = initServerSocket();
    client = allocClient(MAX_CONNEXION);
    max_socket = serveur_socket;
        
    printf("[[INFO] Boss] : Press Enter to Stop the Boss\n");
    for ( ;; ) {
    
        FD_ZERO(&rdfs);
    
        /* Add stdin for stop server */
        FD_SET(STDIN_FILENO, &rdfs);
        /* Add the socket f the server */
        FD_SET(serveur_socket, &rdfs);
        
        /* Add socket of each client */
        for(i = 0; i < total; i++) {
             FD_SET(client[i].id_socket, &rdfs);
        }
        
        if( (i = select(max_socket + 1, &rdfs, NULL, NULL, &tval)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if ( i == 0 ) {
            printf("Time Reach\n");
            tval.tv_sec  = 60;
        }
        
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;            
        }
        else if( FD_ISSET(serveur_socket, &rdfs) ) {
            client[total].id_socket = accept(serveur_socket, (struct sockaddr*) &s_client, (socklen_t *)&struct_size);
            
            max_socket = ((client[total].id_socket > max_socket) ? client[total].id_socket : max_socket);
            strcpy(client[total].ip, inet_ntoa(s_client.sin_addr));
            
            printf("IP address is: %s\n", inet_ntoa(s_client.sin_addr));
            printf("port is: %d\n", (int) ntohs(s_client.sin_port));
            printf("New client [%d]\n\n", client[total].id_socket);
            
            ++total;
        }
        else {    /* A client wrote something */    
            for(i = 0; i < total; i++) {
                if(FD_ISSET(client[i].id_socket, &rdfs)) {                   

                    if ( read(client[i].id_socket, inBuf, 80) == 0 ) {
                        if ( max_socket == client[i].id_socket ) {
                            max_socket = serveur_socket;
                        }
                        
                        printf("Close : %d\n", client[i].id_socket);
                        close(client[i].id_socket);
                        memmove(client + i, client + i + 1, (total - i - 1) * sizeof(Client));
                        
                    }
                    else {
                        /* Remove \r and \n */
                        if((ret = strchr(inBuf, '\r')) != NULL) *ret = '\0'; 
                        if((ret = strchr(inBuf, '\n')) != NULL) *ret = '\0';
                                      
                        printf("[[INFO] Server] : message recu <%s> [Socket : %d]\n", inBuf, client[i].id_socket);
                        
                        if ( strcmp(inBuf, "ListOfCollector") == 0 ) {
                            random = rand() % NB_MAX_COLLECTOR ;
                            if ( random > total ) {
                                random = total;
                            }

                            i = 0; j = 0;
                            printf("Random : %d\n", random);
                            while( j != random ) {
                                if ( rand() % 100 < (random / total * 100) ) {
                                    printf("Value : %d", i);
                                    ++j;
                                    send(client[i].id_socket, client[i].ip, 15, 0);
                                }
                                
                                if ( ++i > total ) {
                                    i = 0;
                                }
                            }

                        
                        }
                    }
                    memset(inBuf, '\0', 80);
                }
            }
        }
    }
    
    for(i = 0; i < total; i++) {
        close(client[i].id_socket);
    }
    close(serveur_socket);
    free(client);
    
    printf("[[INFO] Boss] Welcome to this awesome new project\n");
    
    exit(EXIT_SUCCESS);
}

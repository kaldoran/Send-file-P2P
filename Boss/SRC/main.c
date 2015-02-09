//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include "error.h"
#include "client.h"
#include "server.h"
#include "struct_client.h"

#define NB_MAX_COLLECTOR 9

void removeEndCarac(char *input) {
    char *ret;
    
    if((ret = strchr(input, '\r')) != NULL) *ret = '\0'; 
    if((ret = strchr(input, '\n')) != NULL) *ret = '\0';
}

void sendCollector(Client *client, int number, int total) {
    int i, j, pourcent;
    char outBuf[16];
    i = 0; j = 0;

    pourcent = (int)((float)number / (float)total * 100.);
    printf("Random : %d - Val : %d\n", number, pourcent);
    
    while( j != number ) {
        if ( rand() % 100 <= pourcent ) {
            memset(outBuf, '\0', 16);
            
            printf("Send the : %d", i);
            
            sprintf(outBuf, " %s", client[i].ip);
            outBuf[0] = (char)( ((int) '0') + i );
            
            send(client[i].id_socket, outBuf, 16, 0);
            ++j;
        }
        
        if ( ++i > total ) { i = 0; }
    }
    
    return;
}

int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);
    srand(time(NULL));
    fd_set rdfs;
    int random;
    
    char inBuf[20];
    Client *client;

    int i, total = 0;

    struct timeval tval;
    int server_socket, max_socket;
    
    tval.tv_sec  = 60;
    tval.tv_usec = 0; 

    server_socket = initServer();
    client = allocClient(MAX_CONNEXION);
    max_socket = server_socket;
        
    printf("[[INFO] Boss] : Press Enter to Stop the Boss\n");
    for ( ;; ) {
    
        FD_ZERO(&rdfs);
    
        /* Add stdin for stop server */
        FD_SET(STDIN_FILENO, &rdfs);
        /* Add the socket f the server */
        FD_SET(server_socket, &rdfs);
        
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
        else if( FD_ISSET(server_socket, &rdfs) ) {
            if ( total == MAX_CONNEXION ) {
                printf("I'm So full\n");
            } 
            else {
                max_socket = acceptClient(client, server_socket, &total, max_socket);
            }
        }
        else {    /* A client wrote something */    
            for(i = 0; i < total; i++) {
                if(FD_ISSET(client[i].id_socket, &rdfs)) {                   

                    if ( read(client[i].id_socket, inBuf, 80) == 0 ) {
                        max_socket = removeClient(client, i, &total, max_socket );
                    }
                    else {
                        /* Remove \r and \n */
                        removeEndCarac(inBuf);
                                      
                        printf("[[INFO] Server] : message recu <%s> [Socket : %d]\n", inBuf, client[i].id_socket);
                        
                        if ( strcmp(inBuf, "ListOfCollector") == 0 ) {
                            random = (rand() % NB_MAX_COLLECTOR) + 1;
                            if ( random > total ) { random = total; }
                            
                            sendCollector(client, random, total);              
                        }
                    }
                    memset(inBuf, '\0', 80);
                }
            }
        }
    }
    
    closeServer(client, server_socket, total);
    
    printf("[[INFO] Boss] Welcome to this awesome new project\n");
    
    exit(EXIT_SUCCESS);
}

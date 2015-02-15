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
#include "group.h"
#include "client.h"
#include "server.h"
#include "boolean.h"
#include "block_group.h"

#define NB_MAX_COLLECTOR 9

void removeEndCarac(char *input) {
    char *ret;
    
    if((ret = strchr(input, '\r')) != NULL) *ret = '\0'; 
    if((ret = strchr(input, '\n')) != NULL) *ret = '\0';
}


int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);

    srand(time(NULL));
    
    fd_set rdfs;

    int tmpVal;
    
    char inBuf[20];
    Client tmp;
    
    int i, j;
    blockGroup* block_group;

    struct timeval tval;

    
    tval.tv_sec  = 300;
    tval.tv_usec = 0; 
    
    block_group = newBlockGroup();
    block_group->server_socket = initServer();
    block_group->max_socket = block_group->server_socket;
        
    printf("[[INFO] Boss] : Press Enter to Stop the Boss\n");
    for ( ;; ) {
    
        FD_ZERO(&rdfs);
    
        FD_SET(STDIN_FILENO, &rdfs);                    /* Add stdin for stop server */
        FD_SET(block_group->server_socket, &rdfs);                   /* Add the socket f the server */
        
        for(i = 0; i < block_group->total; i++) {
            for ( j = 0; j < block_group->groups[i]->total; j++ ) {
                FD_SET(block_group->groups[i]->client[j].id_socket, &rdfs);        /* Add socket of each client */
            }
        }
        
        if( (i = select(block_group->max_socket + 1, &rdfs, NULL, NULL, &tval)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if ( i == 0 ) {
            printf("Time Reach\n");
            tval.tv_sec  = 300;
            if ( block_group->total != 0 ) {
                for(i = 0; i < block_group->total; i++) {
                    if ( block_group->groups[i]->flag == FALSE ) {
                        block_group->groups[i]->flag = TRUE;
                        
                        for ( j = 0; j < block_group->groups[i]->total; j++ ) {
                            send(block_group->groups[i]->client[j].id_socket, "ping", 4, 0);
                        }
                        tval.tv_sec  = 1;
                    }
                    else {
                        printf("Check which of them as answer !\n");
                        block_group->groups[i]->flag = FALSE;
                    }
                }        
            }   
        }
        
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;            
        }
        else if( FD_ISSET(block_group->server_socket, &rdfs) ) {
            tmp = acceptClient(block_group->server_socket );
            
            read(tmp.id_socket, inBuf, 80);
            removeEndCarac(inBuf);
            fprintf(stderr, "Read : %s", inBuf);
            
            
            if ( ( tmpVal = addGroup( block_group, inBuf )) == -1 
               || addClient(block_group->groups[tmpVal]->client, tmp, &block_group->groups[tmpVal]->total) == FALSE ) {
                /* Can't create groupe */
                close(tmp.id_socket);
            }
            else {
                if ( block_group->max_socket < tmp.id_socket ) {
                    DEBUG_MSG("Change the max socket\n");
                    block_group->max_socket = tmp.id_socket;
                }
            }                        
        }
        else {    /* A client wrote something */    
            for(i = 0; i < block_group->total; i++) {
                for ( j = 0; j < block_group->groups[i]->total; j++ ) {
                    if(FD_ISSET(block_group->groups[i]->client[j].id_socket, &rdfs)) {                   

                        if ( read(block_group->groups[i]->client[j].id_socket, inBuf, 80) == 0 ) {
                            removeClient(block_group->groups[i]->client, j, &block_group->groups[i]->total, &block_group->max_socket );
                        }
                        else {
                            /* Remove \r and \n */
                            removeEndCarac(inBuf);
                                          
                            printf("[[INFO] Server] : message recu <%s> [Socket : %d]\n", inBuf, block_group->groups[i]->client[j].id_socket);
                            
                            if ( strcmp(inBuf, "ListOfCollector") == 0 ) {
                                tmpVal = (rand() % NB_MAX_COLLECTOR) + 1;
                                if ( tmpVal > block_group->groups[i]->total ) { tmpVal = block_group->groups[i]->total; }
                                
                                sendClient(block_group->groups[i]->client, --tmpVal, block_group->groups[i]->total, i);              
                            }
                            else if ( strcmp(inBuf, "Pong") == 0 ) {
                                printf("Pong received !\n");
                            }
                        }
                        memset(inBuf, '\0', 80);
                    }
                }
            }
        }
    }
    
    for(i = 0; i < block_group->total; i++) {
        closeClientArray(block_group->groups[i]->client, block_group->groups[i]->total);
    }
    freeBlockGroup(block_group);
    closeServer(block_group->server_socket);
    
    printf("[[INFO] Boss] Welcome to this awesome new project\n");
    
    exit(EXIT_SUCCESS);
}

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
#include "windows.h"

#define NB_MAX_COLLECTOR 9

void removeEndCarac(char *input) {
    char *ret;
    
    if((ret = strchr(input, '\r')) != NULL) *ret = '\0'; 
    if((ret = strchr(input, '\n')) != NULL) *ret = '\0';
}


int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);

    initWindows();
    srand(time(NULL));
    
    fd_set rdfs;

    int tmpVal;
    
    char inBuf[20];
    Client tmp;
    
    int i, j;
    blockGroup* block_group;
    Group* group;

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
        
            group = block_group->groups[i];
            for ( j = 0; j < group->total; j++ ) {
                FD_SET(group->client[j].id_socket, &rdfs);        /* Add socket of each client */
            }
        }
        
        if( (i = select(block_group->max_socket + 1, &rdfs, NULL, NULL, &tval)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if ( i == 0 ) {
            printf("Timer Reach\n");
            tval.tv_sec  = 1;
            
            for(i = 0; i < block_group->total; i++) {
                group = block_group->groups[i];
                
                if ( block_group->flag == TRUE ) {
                    askPresence(group);
                } else {
                    checkPresence(group, &block_group->max_socket);
                    tval.tv_sec *= 300;
                }
            }
            
            block_group->flag = !block_group->flag;
  
        }
        
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            printf("Bye bye !");
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
        else {    
            /* A client wrote something */    
            for(i = 0; i < block_group->total; i++) {
            
                group = block_group->groups[i];
                for ( j = 0; j < group->total; j++ ) {
                    
                    if(FD_ISSET(group->client[j].id_socket, &rdfs)) {                   

                        tmpVal = read(group->client[j].id_socket, inBuf, 80);
                        removeEndCarac(inBuf);
                        printf("[[INFO] Server] : (%d) message recu <%s> [Socket : %d]\n", tmpVal, inBuf, group->client[j].id_socket);
                        
                        /* If we read empty thing then the client had been disconnect */
                        if ( tmpVal == 0 
                             || strcmp(inBuf, "notExist") == 0  ) {
                             
                            /* Remove the client from is groups */
                            block_group->max_socket = removeClient(group, j, block_group->max_socket );
                            /* If needed remove the group */
                            if ( &group->total == 0 ) {
                                removeGroup( block_group, i );
                            }
                        }
                        else if ( strcmp(inBuf, "ListOfCollectors") == 0 ) {
                            tmpVal = (rand() % NB_MAX_COLLECTOR) + 1;
                            if ( tmpVal > group->total ) { tmpVal = group->total; }
                            
                            sendClient(group->client, tmpVal, group->total, j);              
                        }
                        else if ( strcmp(inBuf, "exist") == 0 ) {
                            group->checker[j] = 1;
                        }
                        
                        /* reinit input buffer */
                        memset(inBuf, '\0', 80);
                    }
                } /* End of loop on client */
            } /* End of loop on groups */
        } /* End of else */
    } /* End of infinit loop */
    
    printf("End !\n");
    for(i = 0; i < block_group->total; i++) {
        closeClientArray(block_group->groups[i]->client, block_group->groups[i]->total);
    }
    freeBlockGroup(block_group);
    closeServer(block_group->server_socket);
    
    endWindows();
    
    exit(EXIT_SUCCESS);
}

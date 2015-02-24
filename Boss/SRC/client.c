//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.c                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include "socket.h"

#include "error.h"
#include "client.h"
#include "boolean.h"
#include "message.h"


Client *newClientArray(int const number) {

    int i;
    Client *client;
    
    if ( (client = calloc(number, sizeof(*client))) == NULL ) {
        QUIT_MSG("Can't allocate memory for client");
    }

    for ( i = 0; i < number; i++ ) {
        client[i] = initClient();
    }
    return client;
}

void handleNewClient(blockGroup* block_group) {

    int tmpVal;
    Client tmp;
    char inBuf[FILENAME_MAX];
    
    tmp = acceptClient(block_group->server_socket );
    
    read(tmp.id_socket, inBuf, FILENAME_MAX);
    removeEndCarac(inBuf);
                
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
    
    return;
}

void handlerClient(blockGroup* block_group, fd_set* rdfs) {

    int i, j; 
    int tmpVal;
    Group* group;
    char inBuf[READER_SIZE];
    
    for(i = 0; i < block_group->total; i++) {

        group = block_group->groups[i];
        for ( j = 0; j < group->total; j++ ) {
        
            if(FD_ISSET(group->client[j].id_socket, rdfs)) { 
                tmpVal = read(group->client[j].id_socket, inBuf, READER_SIZE);
                removeEndCarac(inBuf);
                
                printf("[[INFO] Server] : (%d) message recu <%s> [Socket : %d]\n", tmpVal, inBuf, group->client[j].id_socket);
                
                if ( tmpVal == 0 || strcmp(inBuf, FILE_NOT_EXIST_MSG) == 0  ) {
                     
                    block_group->max_socket = removeClient(group, j, block_group->max_socket );
                    
                    if ( group->total == 0 ) { removeGroup( block_group, i );  } /* If needed remove the group */
                }
                else if ( strcmp(inBuf, LIST_OF_COLLECTOR_MSG) == 0 ) {
                    tmpVal = (rand() % MAX_CONNEXION) + 1;
                    if ( tmpVal > group->total ) { tmpVal = group->total; }
                    
                    sendClient(group->client, tmpVal, group->total, j);              
                }
                else if ( strcmp(inBuf, FILE_EXIST_MSG) == 0 ) {
                    group->checker[j] = 1;
                }
                
                memset(inBuf, '\0', READER_SIZE);  /* reinit input buffer */
            }
        }
    }
    
    return;
}

void closeClientArray(Client *client,int const total) {
    int i;
    for(i = 0; i < total; i++) {
        closesocket(client[i].id_socket);
    }
    
    return;
}

void freeClientArray(Client *client) {
    free(client);
}

Client initClient() {
    Client c;
          
    c.id_socket = socket(AF_INET,SOCK_STREAM,0); 
      
    if (c.id_socket == -1) {
        QUIT_MSG("Can't initiliaze the socket");
    }
    
    return c;
}

Client acceptClient( int const server_socket ) {
    Client new_client;
    SOCKADDR_IN s_client;
    int struct_size;

    struct_size = sizeof(SOCKADDR_IN);
    
    new_client.id_socket = accept(server_socket, (struct sockaddr*) &s_client, (__socklen_t *)&struct_size);

    printf("New client [%d]\n\n", new_client.id_socket);
    printf("IP address is: %s\n", inet_ntoa(s_client.sin_addr));
    printf("port is: %d\n", (int) ntohs(s_client.sin_port));

    strcpy(new_client.ip, inet_ntoa(s_client.sin_addr));

    return new_client;
}

void sendClient(Client *client, int number, int total, int to) {
    int i, pourcent;
    char outBuf[20];
    i = 0;

    pourcent = (int)((float)number / (float)total * 100.);
    printf("Random : %d - Val : %d\n", number, pourcent);

    while( number > 0) {
        if ( rand() % 100 <= pourcent ) {
            --number;
            memset(outBuf, '\0', 20);

            sprintf(outBuf, "%d|", number);
            strcat(outBuf, client[i].ip);
            
            send(client[to].id_socket, outBuf, 20, 0);
        }

        if ( ++i > total ) { i = 0; }
    }
        
    return;
}

bool addClient(Client *client, Client new, int *total) {
    if ( *total != MAX_CONNEXION ) {
        
        client[*total] = new;
        ++(*total);
        
        return TRUE;
    }
    
    printf("I'm So full !\n");
    return FALSE;
}

int removeClient(Group *group, int const pos, int const max_socket ) {
    int i, new_max_socket;
    printf("Close : %d\n", group->client[pos].id_socket);
    
    new_max_socket = -1;
    
    /* Seek new socket max */
    if ( max_socket == group->client[pos].id_socket ) {
        for ( i = 0; i < group->total; i++) {
            if ( i != pos 
                && group->client[i].id_socket > new_max_socket ) {
                
                new_max_socket = group->client[i].id_socket;
            }
        }
    }

    close(group->client[pos].id_socket);
    
    /* Move memory to avoid blank into array */
    memmove((group->client) + pos, (group->client) + pos + 1, (group->total - pos - 1) * sizeof(*group->client));  
    memmove((group->checker) + pos, (group->checker) + pos + 1, (group->total - pos - 1) * sizeof(*group->checker));  
    
    --(group->total);
    
    if ( new_max_socket == -1 ) {
        return max_socket;
    }
    
    return new_max_socket;
}

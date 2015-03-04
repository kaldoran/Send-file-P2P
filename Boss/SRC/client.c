//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.c                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifdef WIN32
    #define __socklen_t int
#endif // WIN32

#include <stdlib.h>
#include <string.h>

#include "tcp.h"
#include "socket.h"
#include "error.h"
#include "client.h"
#include "boolean.h"
#include "message.h"

#define SEND_CLIENT_BUFFER 30

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
    char *file; /* Pointer on file name */
    char *port; /* Pointer on port */
    char inBuf[FILENAME_MAX] = "";
    
    tmp = acceptClient(block_group->server_socket );

    /* Received a new message */
    if ( tcpActionDelay(tmp, inBuf, FILENAME_MAX, 1, 50000) < 0 ) {
        printf("[ERROR] Client %d does not send information in time\n", tmp.id_socket);
    }
    removeEndCarac(inBuf);
    
    DEBUG_MSG("Received First message : %s", inBuf);
    
    /* Split message for file name */
    if (   ( file = strtok(inBuf, "|") ) == NULL 
        || ( port = strtok(NULL, "|") ) == NULL
        || (tmpVal = atoi(port)) < 0  
        || tmpVal > 65536 ) {
        
        DEBUG_MSG("Close the socket !");
        closesocket(tmp.id_socket);
        return; 
    }
    
    printf("\t - File : %s\n", file);
    printf("\t - Port : %s\n", port);
    strcpy(tmp.port, port);

    if ( ( tmpVal = addGroup( block_group, file )) == -1 
       || addClient(block_group->groups[tmpVal]->client, tmp, &block_group->groups[tmpVal]->total) == FALSE ) {
        /* Can't create groupe */
        DEBUG_MSG("Can't create group !");
        closesocket(tmp.id_socket);
        return;
    }
    else {
        if ( block_group->max_socket < tmp.id_socket ) {
            DEBUG_MSG("Change the max socket");
            block_group->max_socket = tmp.id_socket;
        }
    }  
    
    return;
}

void handlerClient(blockGroup* block_group, fd_set* rdfs) {

    int i, j; 
    int tmpVal;
    Group* group;
    char inBuf[READER_SIZE] = "";
    
    for(i = 0; i < block_group->total; i++) {
    
        group = block_group->groups[i];
        for ( j = 0; j < group->total; j++ ) {

            if(FD_ISSET(group->client[j].id_socket, rdfs)) { 

                tmpVal = recv(group->client[j].id_socket, inBuf, READER_SIZE, 0);
                removeEndCarac(inBuf);
                
                if ( tmpVal != 0 ) {
                    printf("\n[INFO] (%d) message recu '%s' [Client : %d]\n", tmpVal, inBuf, group->client[j].id_socket);
                } 
                
                if ( tmpVal == 0 || strcmp(inBuf, FILE_NOT_EXIST_MSG) == 0  ) {                    
                    block_group->max_socket = removeClient(group, j, block_group->server_socket );
                    --j; /* We remove a client, so group->total - 1, then we apply it to j */
                    if ( group->total == 0 ) { removeGroup( block_group, i );  --i; } /* If needed remove the group */
                }
                else if ( strcmp(inBuf, LIST_OF_COLLECTOR_MSG) == 0 ) {
                    sendClient(group->client, group->total, j);    
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

void closeClientArray(Client *client, int const total) {
    int i;
    for(i = 0; i < total; i++) {
        printf("[KICK] Stop socket of client %d\n", client[i].id_socket);
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
    Client new_client = initClient();
    SOCKADDR_IN s_client = { 0 };
    int struct_size;

    struct_size = sizeof(SOCKADDR_IN);
    
    new_client.id_socket = accept(server_socket, (struct sockaddr*) &s_client, (__socklen_t *)&struct_size);

    printf("\n[INFO] New client [%d]\n\t - Ip : %s\n", new_client.id_socket, inet_ntoa(s_client.sin_addr));

    strcpy(new_client.ip, inet_ntoa(s_client.sin_addr));

    return new_client;
}

void sendClient(Client *client, int total, int to) {
    
    int i = 0, pourcent = 100, number = (total > 10) ? MAX_COLLECTOR_SEND : total - 1; /* We send all list -1 ( cause of it self ) */
    char outBuf[SEND_CLIENT_BUFFER];

    if ( total == 1 ) {
        printf("[INFO] Client %d is alone\n", client[to].id_socket);
        send(client[to].id_socket, ALONE_COLLECTOR_MSG, sizeof(ALONE_COLLECTOR_MSG), 0);
        return;
    }
    
    printf("[INFO] List Of Collector Send : \n");
    pourcent = (int)( ((float) MAX_COLLECTOR_SEND / total) * 100.);
    if ( pourcent <= 0 ) {
        pourcent = 1; /* At least 1 pourcent chance for each collector */
    }
    DEBUG_MSG("Send %d collectors - Pourcent : %d\n", number, pourcent);
    
    while( number > 0) {
        if ( rand() % 100 <= pourcent 
            && client[i].id_socket != client[to].id_socket) {
            
            --number;
            memset(outBuf, '\0', SEND_CLIENT_BUFFER);
            sprintf(outBuf, "%d|%s|%s", number, client[i].ip, client[i].port);
            printf("\t - Client %d [%s:%s]\n", client[i].id_socket, client[i].ip, client[i].port);
            send(client[to].id_socket, outBuf, SEND_CLIENT_BUFFER, 0);
        }

        if ( ++i >= total ) { i = 0; }        
    }
        
    return;
}

bool addClient(Client *client, Client new, int *total) {
    if ( *total != MAX_CONNEXION ) {
        
        client[*total] = new;
        ++(*total);
        
        return TRUE;
    }
    
    printf("[ERROR] No more client can connect !\n");
    return FALSE;
}

int removeClient(Group *group, int const pos, int const max_socket ) {
    int i, new_max_socket;
    printf("[INFO] Client %d disconnect\n\n", group->client[pos].id_socket);
   
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

    closesocket(group->client[pos].id_socket);
    
    /* Move memory to avoid blank into array */
    memmove((group->client) + pos, (group->client) + pos + 1, (group->total - pos - 1) * sizeof(*group->client));  
    memmove((group->checker) + pos, (group->checker) + pos + 1, (group->total - pos - 1) * sizeof(*group->checker));  
    
    --(group->total);

    if ( new_max_socket == -1 ) {
        return max_socket;
    }
    
    return new_max_socket;
}

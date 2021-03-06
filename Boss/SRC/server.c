//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.c                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#include <string.h>

#include "error.h"
#include "socket.h"
#include "ping.h"
#include "server.h"
#include "client.h"
#include "block_group.h"

int initServer() {
    int optionVal = 1;
    int struct_size, serveur_socket;
    SOCKADDR_IN s_serveur = { 0 };
    struct_size = sizeof(SOCKADDR_IN);
        
    s_serveur.sin_family = AF_INET;
    s_serveur.sin_addr.s_addr = INADDR_ANY;
    s_serveur.sin_port = htons(PORT);    
    
    if ( (serveur_socket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR ){
        QUIT_MSG("Can't create the socket : ");
    }

    if ( setsockopt(serveur_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&optionVal, sizeof(optionVal)) == SOCKET_ERROR ) {
        QUIT_MSG("Can't set socket option : ");
    }
    
    if ( bind(serveur_socket, (struct sockaddr *)&s_serveur, struct_size) == SOCKET_ERROR ){
        QUIT_MSG("Can't bind the socket : ");
    }
    
    /* Hey listen */
    if ( listen(serveur_socket,MAX_CONNEXION) == SOCKET_ERROR ){
        QUIT_MSG("Socket listen trouble : ");
    }
    
    return serveur_socket;
}

void startServer() {
    int timer;
    fd_set rdfs;
    blockGroup* block_group;
    struct timeval tval;
    
    tval.tv_sec  = PING_TIMER;
    tval.tv_usec = 0; 
    
    block_group = newBlockGroup();
    block_group->server_socket = initServer();
    block_group->max_socket = block_group->server_socket;
            
    printf("[IMPORTANT] : Press Enter to Stop the Boss\n");  
    
    for ( ;; ) {
    
        FD_ZERO(&rdfs);
        setHandler(block_group, &rdfs);
    
        if( (timer = select(block_group->max_socket + 1, &rdfs, NULL, NULL, &tval)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if ( timer == 0 ) {
            tval.tv_sec = handlerPresence(block_group);  
        }

        #ifdef linux
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;            
        }
        else
        #endif 
        if( FD_ISSET(block_group->server_socket, &rdfs) ) {
            handleNewClient(block_group);      
        }
        else {
            handlerClient(block_group, &rdfs);
        }
    }
    
    printf("[BYE] Server stop\n\n");
    closeServer(block_group);
    
    return;
    
}

void setHandler(blockGroup *block_group, fd_set *rdfs) {
    int i, j;
    Group* group;
    
    #ifdef linux
    FD_SET(STDIN_FILENO, rdfs);                                /* Add stdin for stop server */
    #endif
    FD_SET(block_group->server_socket, rdfs);                  /* Add the socket f the server */
    
    for(i = 0; i < block_group->total; i++) {
    
        group = block_group->groups[i];
        for ( j = 0; j < group->total; j++ ) {
            FD_SET(group->client[j].id_socket, rdfs);          /* Add socket of each client */
        }
    }
    
    return;       
}

void closeServer(blockGroup *block_group) {
    int i;
    for(i = 0; i < block_group->total; i++) {
        closeClientArray(block_group->groups[i]->client, block_group->groups[i]->total);
    }
    closesocket(block_group->server_socket);
    freeBlockGroup(block_group);

    return;
}
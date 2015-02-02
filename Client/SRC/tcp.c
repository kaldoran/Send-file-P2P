//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : tcp.c                                          |
// DATE : 01/02/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include "tcp.h"
#include "error.h"

    
void new_socket(Index *index) {

    index->id_socket = socket(AF_INET,SOCK_STREAM,0); 
    
    if (index->id_socket == -1) {
        QUIT_MSG("Can't create the socket");
    }
}

bool tcp_start(Index *index) {
    struct sockaddr_in serv;
    size_t serv_length = sizeof(serv);
    
    memset(&serv, 0, serv_length);
    serv.sin_family = AF_INET;
    serv.sin_port = index->port;
    serv.sin_addr.s_addr = index->ip;

    if (connect(index->id_socket, (struct sockaddr *)&serv, serv_length) < 0){
        close(index->id_socket);
        return FALSE;
    }
    
    return TRUE;
}

int tcp_action(Index *index, void *data, int data_length, int type) {
    
    if ( type == SEND ) 
        return send(index->id_socket, data, data_length, 0);
    else if ( type == RECEIVED ) {
        return recv(index->id_socket, data, data_length, 0);
    }
    else 
        return -1;
}
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

    
Socket* new_socket() {
    Socket* s = calloc(1 , sizeof(*s));
    
    s->id_socket = socket(AF_INET,SOCK_STREAM,0); 
    
    if (s->id_socket == -1) {
        QUIT_MSG("Can't create the socket");
    }
    
    return s;
}

void free_socket(Socket *s) {
    free(s);
}

bool tcp_start(Socket *s) {
    struct sockaddr_in serv;
    size_t serv_length = sizeof(serv);
    
    memset(&serv, 0, serv_length);
    serv.sin_family = AF_INET;
    serv.sin_port = s->port;
    serv.sin_addr.s_addr = s->ip;

    if (connect(s->id_socket, (struct sockaddr *)&serv, serv_length) < 0){
        close(s->id_socket);
        return FALSE;
    }
    
    return TRUE;
}

int tcp_action(Socket *s, void *data, int data_length, int type) {
    
    if ( type == SEND ) 
        return send(s->id_socket, data, data_length, 0);
    else if ( type == RECEIVED ) {
        return recv(s->id_socket, data, data_length, 0);
    }
    else 
        return -1;
}
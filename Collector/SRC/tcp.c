//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : tcp.c                                          |
// DATE : 01/02/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"

#include "tcp.h"
#include "error.h"

    
SOCKET new_socket() {
    Socket s;
    
    s = socket(AF_INET,SOCK_STREAM,0); 
    
    if (s->id_socket == -1) {
        QUIT_MSG("Can't create the socket");
    }
    
    return s;
}

bool tcp_start(SOCKET s, struct sockaddr_in ) {
    struct sockaddr_in serv;
    size_t serv_length = sizeof(serv);
    
    memset(&serv, 0, serv_length);
    serv.sin_family = AF_INET;
    serv.sin_port = s->port;
    serv.sin_addr.s_addr = s->ip;

    if (connect(s, (struct sockaddr *)&serv, serv_length) < 0){
        close(s);
        return FALSE;
    }
    
    return TRUE;
}

int tcp_action(SOCKET s, void *data, int data_length, int type) {
    
    if ( type == SEND ) 
        return send(s, data, data_length, 0);
    else if ( type == RECEIVED ) {
        return recv(s, data, data_length, 0);
    }
    else 
        return -1;
}
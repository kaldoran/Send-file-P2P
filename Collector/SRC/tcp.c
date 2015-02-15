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

    
SOCKET newSocket() {
    SOCKET s;
    
    s = socket(AF_INET,SOCK_STREAM,0); 
    
    if (s == -1) {
        QUIT_MSG("Can't create the socket");
    }
    
    return s;
}

bool tcpStart(SOCKET s, SOCKADDR_IN serv ) {

    size_t serv_length = sizeof(serv);
    
    if (connect(s, (struct sockaddr *)&serv, serv_length) < 0){
        close(s);
        return FALSE;
    }
    
    return TRUE;
}

int tcpAction(SOCKET s, void *data, int data_length, int type) {
    
    if ( type == SEND ) 
        return send(s, data, data_length, 0);
    else if ( type == RECEIVED ) {
        return recv(s, data, data_length, 0);
    }
    else 
        return -1;
}
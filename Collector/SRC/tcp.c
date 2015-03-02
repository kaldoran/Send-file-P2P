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

bool tcpStart(Client c) {

    size_t serv_length = sizeof(c.sock_info);
    
    if (connect(c.id_socket, (struct sockaddr *)&(c.sock_info), serv_length) < 0){
        closesocket(c.id_socket);
        return FALSE;
    }
    
    return TRUE;
}

int tcpAction(Client c, void *data, int data_length, int type) {
    
    if ( type == SEND ) {
        DEBUG_MSG("[INFO] SEND : '%s' to %d", (char *)data, c.id_socket);
        return send(c.id_socket, data, data_length, 0);
    }
    else if ( type == RECEIVED ) {
        return recv(c.id_socket, data, data_length, 0);
    }
   
    return -1;

}

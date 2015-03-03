//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : tcp.c                                          |
// DATE : 01/02/15                                          |
//----------------------------------------------------------

#include "socket.h"
#include "tcp.h"

int tcpAction(Client c, void *data, int data_length, int type) {
    
    if ( type == SEND ) {
        return send(c.id_socket, data, data_length, 0);
    }
    else if ( type == RECEIVED ) {
        return recv(c.id_socket, data, data_length, 0);
    }
   
    return -1;
}

int tcpActionDelay(Client c, void *data, int data_length, int second, int millisecond ) {
    struct timeval tv;
    
    tv.tv_sec = second;
    tv.tv_usec = millisecond; 
    
    setsockopt(c.id_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval)); /* Set a timer on respond */
    return tcpAction(c, data, data_length, RECEIVED);
} 
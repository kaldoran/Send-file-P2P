//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : tcp.c                                          |
// DATE : 01/02/15                                          |
//----------------------------------------------------------

#include "tcp.h"
#include "error.h"
#include "socket.h"

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

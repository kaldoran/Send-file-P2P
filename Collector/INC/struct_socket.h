//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_socket.c                                |
// DATE : 08/02/15                                          |
//----------------------------------------------------------
#ifndef STRUCT_SOCKET_H
#define STRUCT_SOCKET_H

typedef struct Socket {
    int id_socket; 
    in_addr_t ip;
    in_port_t port;
} Socket;

#endif

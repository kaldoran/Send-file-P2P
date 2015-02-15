//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : tcp.h                                          |
// DATE : 01/02/15                                          |
//----------------------------------------------------------

#ifndef TCP_H
#define TCP_H

#define SEND 0
#define RECEIVED 1

#if DEBUG
    #define AFFICHE(DATA) printf("Recu : %s.\n", (char *)DATA);
#else 
    #define AFFICHE(DATA) ;
#endif

#include "socket.h"
#include "boolean.h"

SOCKET newSocket();

void freeSocket(SOCKET s);

bool tcpStart(SOCKET s, SOCKADDR_IN serv );

int tcpAction(SOCKET s, void *data, int data_length, int type);

#endif /* TCP_H included */
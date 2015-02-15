//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_client.c                                |
// DATE : 08/02/15                                          |
//----------------------------------------------------------
#ifndef STRUCT_CLIENT_H
#define STRUCT_CLIENT_H

#include "socket.h"

#define MAX_CONNEXION 15

typedef struct Client {
    SOCKET id_socket; 
    char ip[15];
} Client;

#endif

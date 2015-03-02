//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_client.h                                |
// DATE : 08/02/15                                          |
//----------------------------------------------------------
#ifndef STRUCT_CLIENT_H
#define STRUCT_CLIENT_H

#include "socket.h"

#define MAX_CONNEXION 15

typedef struct Client {
    SOCKET id_socket;       /* id of the socket */
    char ip[16];            /* ip associate with the socket */
    char port[6];
} Client;

#endif /* STRUCT_CLIENT_H included */

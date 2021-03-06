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
    SOCKET id_socket;       // Id of the socket opened by the Client.
    SOCKADDR_IN sock_info;  // Client's adress.
} Client;

#endif /* STRUCT_CLIENT_H included */

//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "struct_client.h"

#define MAX_CONNEXION 1

int initServer();

void closeServer(Client *client, int server_socket, int const total);

#endif /* SERVER_H included */
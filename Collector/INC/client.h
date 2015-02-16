//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.h                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H

#include "boolean.h"
#include "struct_client.h"

Client *newClientArray(int const number);

void closeClientArray(Client *client,int const total);

void freeClientArray(Client *client);

Client initClient();

Client acceptClient( int const server_socket );

bool addClient(Client *client, Client new, int *total);

void removeClient(Client *client, int const pos,  int *total, int *max_socket);

#endif /* CLIENT_H included */
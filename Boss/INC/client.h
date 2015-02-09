//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H

#include "struct_client.h"

Client *allocClient(int number);

int acceptClient(Client *client, int const server_socket, int *total, int const max_socket );

void sendClient(Client *client, int number, int total, int to);

int removeClient(Client *client, int const pos,  int *total, int const max_socket);

#endif /* CLIENT_H included */
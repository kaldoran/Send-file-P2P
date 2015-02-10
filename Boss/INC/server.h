//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "struct_client.h"

int initServer();

void closeServer(int server_socket);

#endif /* SERVER_H included */
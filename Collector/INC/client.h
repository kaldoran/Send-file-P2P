//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.h                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H

#include "struct_client.h"

Client newClient();

Client acceptClient( int const server_socket );

#endif /* CLIENT_H included */
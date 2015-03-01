//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_server.h                                |
// DATE : 01/03/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_SERVER_H
#define STRUCT_SERVER_H

#include <stdlib.h>

#include "boolean.h"
#include "socket.h"

typedef struct Server {
    SOCKET seed_socket;
    int max_socket;
    
    int nb_seed;
    
    FILE *file;
    bool full_file;
    
    Client *client;
    int nb_leach;
} Server;

#endif /* STRUCT_SERVER_H included */
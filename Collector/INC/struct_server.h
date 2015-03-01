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
    SOCKET seed_socket;     // Socket for the server
    int max_socket;         // Max id of all socket
    
    int nb_seed;            // Total number of seeder
    
    FILE *file;             // File on which we write 
    bool full_file;         // Boolean that indicate if file is full
    
    Client *client;         // List of client
    int nb_leach;           // Total number of leacher
} Server;

#endif /* STRUCT_SERVER_H included */
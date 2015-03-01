//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.c                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#include <unistd.h>

#include "error.h"
#include "client.h"
#include "server.h"
#include "boolean.h"

Server* newServer(const int port) {
    Server* s; 

    if ( (s = calloc(1, sizeof(*s))) == NULL ) {
        QUIT_MSG("Can't allocate new server");
    }

    s->seed_socket = initServer(port);
    s->max_socket = s->seed_socket;
    s->client = newClientArray(MAX_CONNEXION);
    
    s->file = NULL;
    
    s->nb_leach = 0;
    s->nb_seed = 0;
    s->full_file = FALSE;

    return s;
}

void freeServer(Server *s) {
    if ( s->file != NULL ) {
        fclose(s->file);
    }
    
    freeClientArray(s->client);
    free(s);

    return;
}

int initServer(const int port) {
    int struct_size, serveur_socket;
    SOCKADDR_IN s_serveur;
    struct_size = sizeof(SOCKADDR_IN);
        
    s_serveur.sin_family = AF_INET;
    s_serveur.sin_addr.s_addr = INADDR_ANY;
    s_serveur.sin_port = htons(port);    
    
    if ( (serveur_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        QUIT_MSG("Can't create the socket : ");
    }

    if ( bind(serveur_socket, (struct sockaddr *)&s_serveur, struct_size) == -1){
        QUIT_MSG("Can't bind the socket : ");
    }
    
    /* Hey listen */
    if ( listen(serveur_socket,MAX_CONNEXION) == -1 ){
        QUIT_MSG("Socket listen trouble : ");
    }
    
    return serveur_socket;
}

void closeServer(int server_socket) {

    close(server_socket);
    
    return;
}

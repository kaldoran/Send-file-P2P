//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.c                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------
#include <arpa/inet.h>
#include <unistd.h>

#include "error.h"
#include "server.h"

#define PORT 42000

int initServer() {
    int struct_size, serveur_socket;
    struct sockaddr_in s_serveur;
    struct_size = sizeof(struct sockaddr_in);
        
    s_serveur.sin_family = AF_INET;
    s_serveur.sin_addr.s_addr = INADDR_ANY;
    s_serveur.sin_port = htons(PORT);    
    
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

void closeServer(Client *client, int server_socket, int const total) {
    int i;
    for(i = 0; i < total; i++) {
        close(client[i].id_socket);
    }
    close(server_socket);
    
    return;
}
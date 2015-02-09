//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.c                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#include <string.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "error.h"
#include "client.h"


Client *allocClient(int number) {
    Client *client;
    
    if ( (client = calloc(number, sizeof(client))) == NULL ) {
        QUIT_MSG("Can't allocate memory for client");
    }

    return client;
}

int acceptClient(Client *client, int const server_socket, int *total, int const max_socket) {

    struct sockaddr_in s_client;
    int struct_size , new_max_socket;
    struct_size = sizeof(struct sockaddr_in);
    
    client[*total].id_socket = accept(server_socket, (struct sockaddr*) &s_client, (socklen_t *)&struct_size);
            
    strcpy(client[*total].ip, inet_ntoa(s_client.sin_addr));
         
    printf("IP address is: %s\n", inet_ntoa(s_client.sin_addr));
    printf("port is: %d\n", (int) ntohs(s_client.sin_port));
    printf("New client [%d]\n\n", client[*total].id_socket);
         
    new_max_socket = ((client[*total].id_socket > max_socket) ? client[*total].id_socket : max_socket);
    ++(*total);
    
    return new_max_socket;
}


int removeClient(Client *client, int const pos,  int *total, int const max_socket ) {
    int i, new_max_socket;
    printf("Close : %d\n", client[pos].id_socket);
    
    new_max_socket = max_socket;
    
    /* Seek new socket max */
    if ( max_socket == client[pos].id_socket ) {
        for ( i = 0; i < *total; i++) {
            if ( client[i].id_socket > new_max_socket ) {
                new_max_socket = client[i].id_socket;
            }
        }
    }

    close(client[pos].id_socket);
    
    /* Move memory to avoid blank into array */
    memmove(client + pos, client + pos + 1, (*total - pos - 1) * sizeof(Client));  
    
    --(*total);
    
    return new_max_socket;
}
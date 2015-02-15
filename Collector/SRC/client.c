//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.c                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#include <string.h>

#include "error.h"
#include "client.h"

Client newClient() {
    Client c;
    
    memset(&c.sock_info, 0, sizeof(c.sock_info) );
      
    c.id_socket = socket(AF_INET,SOCK_STREAM,0); 
  
    c.sock_info.sin_family = AF_INET;
    
    if (c.id_socket == -1) {
        QUIT_MSG("Can't create the socket");
    }
    
    return c;
}

Client acceptClient( int const server_socket ) {
    Client new_client = newClient();

    int struct_size;

    struct_size = sizeof(SOCKADDR_IN);
    
    new_client.id_socket = accept(server_socket, (struct sockaddr*) &new_client.sock_info, (socklen_t *)&struct_size);

    printf("New client [%d]\n\n", new_client.id_socket);
    printf("IP address is: %s\n", inet_ntoa(new_client.sock_info.sin_addr));
    printf("port is: %d\n", (int) ntohs(new_client.sock_info.sin_port));

    return new_client;
}
//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : collector.c                                    |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#include <string.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "error.h"
#include "client.h"
#include "boolean.h"


Collector *newClient(int const number) {
    Collector *client;
    
    if ( (client = calloc(number, sizeof(*client))) == NULL ) {
        QUIT_MSG("Can't allocate memory for client");
    }

    return client;
}


void closeClient(Collector *client,int const total) {
    int i;
    for(i = 0; i < total; i++) {
        close(client[i].id_socket);
    }
}

void freeClient(Collector *client) {
    free(client);
}


Collector acceptClient( int const server_socket ) {
    Collector new_client;
    struct sockaddr_in s_client;
    int struct_size;

    struct_size = sizeof(struct sockaddr_in);
    
    new_client.id_socket = accept(server_socket, (struct sockaddr*) &s_client, (socklen_t *)&struct_size);

    printf("New client [%d]\n\n", new_client.id_socket);
    printf("IP address is: %s\n", inet_ntoa(s_client.sin_addr));
    printf("port is: %d\n", (int) ntohs(s_client.sin_port));

    strcpy(new_client.ip, inet_ntoa(s_client.sin_addr));

    return new_client;
}

void sendClient(Collector *client, int number, int total, int to) {
    int i, pourcent;
    char outBuf[16];
    i = 0;

    pourcent = (int)((float)number / (float)total * 100.);
    DEBUG_MSG("Random : %d - Val : %d\n", number, pourcent);

    while( number >= 0) {
        if ( rand() % 100 <= pourcent ) {
            memset(outBuf, '\0', 16);
            
            printf("Send the : %d\n", i);
            
            sprintf(outBuf, " %s", client[i].ip);
            outBuf[0] = (char)( ((int) '0') + number );
            
            send(client[to].id_socket, outBuf, 16, 0);
            --number;
        }
        
        if ( ++i > total ) { i = 0; }
    }
    
    return;
}

bool addClient(Collector *client, Client new, int *total) {
    if ( *total != MAX_CONNEXION ) {
        
        client[*total] = new;
        ++(*total);
        
        return TRUE;
    }
    
    printf("I'm So full !\n");
    return FALSE;
}

void removeClient(Collector *client, int const pos,  int *total, int *max_socket ) {
    int i, new_max_socket;
    printf("Close : %d\n", client[pos].id_socket);
    
    new_max_socket = *max_socket;
    
    /* Seek new socket max */
    if ( *max_socket == client[pos].id_socket ) {
        for ( i = 0; i < *total; i++) {
            if ( client[i].id_socket > new_max_socket ) {
                new_max_socket = client[i].id_socket;
            }
        }
    }

    close(client[pos].id_socket);
    
    /* Move memory to avoid blank into array */
    memmove(client + pos, client + pos + 1, (*total - pos - 1) * sizeof(Client));  
    
    *max_socket = new_max_socket;
    --(*total);
    
    return;
}
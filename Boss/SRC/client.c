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
#include "boolean.h"


Client *newClientArray(int const number) {
    int i ;
    Client *client;
    
    if ( (client = calloc(number, sizeof(*client))) == NULL ) {
        QUIT_MSG("Can't allocate memory for client");
    }

    for ( i = 0; i < number; i++ ) {
        client[i] = initClient();
    }
    return client;
}


void closeClientArray(Client *client,int const total) {
    int i;
    for(i = 0; i < total; i++) {
        closesocket(client[i].id_socket);
    }
}

void freeClientArray(Client *client) {
    free(client);
}

Client initClient() {
    Client c;
          
    c.id_socket = socket(AF_INET,SOCK_STREAM,0); 
      
    if (c.id_socket == -1) {
        QUIT_MSG("Can't create the socket");
    }
    
    return c;
}


Client acceptClient( int const server_socket ) {
    Client new_client;
    SOCKADDR_IN s_client;
    int struct_size;

    struct_size = sizeof(SOCKADDR_IN);
    
    new_client.id_socket = accept(server_socket, (struct sockaddr*) &s_client, (socklen_t *)&struct_size);

    printf("New client [%d]\n\n", new_client.id_socket);
    printf("IP address is: %s\n", inet_ntoa(s_client.sin_addr));
    printf("port is: %d\n", (int) ntohs(s_client.sin_port));

    strcpy(new_client.ip, inet_ntoa(s_client.sin_addr));

    return new_client;
}

void sendClient(Client *client, int number, int total, int to) {
    int i, pourcent;
    char outBuf[20];
    i = 0;

    pourcent = (int)((float)number / (float)total * 100.);
    printf("Random : %d - Val : %d\n", number, pourcent);

    while( number > 0) {
        if ( rand() % 100 <= pourcent ) {
            --number;
            memset(outBuf, '\0', 20);

            sprintf(outBuf, "%d|", number);
            strcat(outBuf, client[i].ip);
            
            send(client[to].id_socket, outBuf, 20, 0);
        }

        if ( ++i > total ) { i = 0; }
    }
        
    return;
}

bool addClient(Client *client, Client new, int *total) {
    if ( *total != MAX_CONNEXION ) {
        
        client[*total] = new;
        ++(*total);
        
        return TRUE;
    }
    
    printf("I'm So full !\n");
    return FALSE;
}

int removeClient(Group *group, int const pos, int const max_socket ) {
    int i, new_max_socket;
    printf("Close : %d\n", group->client[pos].id_socket);
    
    new_max_socket = -1;
    
    /* Seek new socket max */
    if ( max_socket == group->client[pos].id_socket ) {
        for ( i = 0; i < group->total; i++) {
            if ( i != pos 
                && group->client[i].id_socket > new_max_socket ) {
                
                new_max_socket = group->client[i].id_socket;
            }
        }
    }

    close(group->client[pos].id_socket);
    
    /* Move memory to avoid blank into array */
    memmove((group->client) + pos, (group->client) + pos + 1, (group->total - pos - 1) * sizeof(*group->client));  
    memmove((group->checker) + pos, (group->checker) + pos + 1, (group->total - pos - 1) * sizeof(*group->checker));  
    
    --(group->total);
    
    if ( new_max_socket == -1 ) {
        return max_socket;
    }
    
    return new_max_socket;
}

void askPresence(Group *group) {
    int i;

    for ( i = 0; i < group->total; i++ ) {
        /* Send the same message to all client from a groups */
        send(group->client[i].id_socket, group->name, sizeof(*group->name), 0);
    }   
    return;  
}

void checkPresence(Group *group, int *max_socket) {
    int i;
    
    for ( i = 0; i < group->total; i++ ) {
        /* if the ckerckers flag if at 0 then i didn't respond in time */
        if ( group->checker[i] == 0 ) {
            *max_socket = removeClient(group, i, *max_socket );
        }
    }

    return;
}
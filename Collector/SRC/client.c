//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.c                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#ifdef WIN32
    #define __socklen_t int
#endif // WIN32

#include <string.h>

#include "error.h"
#include "client.h"

Client *newClientArray(int const number) {
    int i;
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

void freeClientArray(Client *client, int const total) {
    closeClientArray(client, total);
    
    free(client);
}

Client initClient() {
    Client c;
    
    memset(&c.sock_info, 0, sizeof(c.sock_info));
      
    c.id_socket = socket(AF_INET,SOCK_STREAM,0); 
  
    c.sock_info.sin_family = AF_INET;
    
    if (c.id_socket == -1) {
        QUIT_MSG("Can't create the socket");
    }
    
    return c;
}

Client acceptClient( int const server_socket ) {
    Client new_client = initClient();

    int struct_size;

    struct_size = sizeof(SOCKADDR_IN);
    
    new_client.id_socket = accept(server_socket, (struct sockaddr*) &new_client.sock_info, (__socklen_t *)&struct_size);

    printf("\n[INFO] New client [%d]\n", new_client.id_socket);
    printf("\t - Ip of client : %s\n", inet_ntoa(new_client.sock_info.sin_addr));

    return new_client;
}

int addClient(Server* s){
    Client tmp = acceptClient(s->seed_socket);
            
    if(s->nb_leach < MAX_CONNEXION) {
        if ( s->max_socket < tmp.id_socket ) {
            DEBUG_MSG("Change the max socket.");
            s->max_socket = tmp.id_socket;
        }

        s->client[s->nb_leach] = tmp;
        
        return 1;
    }
    
    printf("[INFO] Max number of client reached.\n");
    closesocket(tmp.id_socket);
    
    return 0;
}

void removeClient(Server* s, int const pos) {
    int i, new_max_socket;
    printf("[INFO] Client %d disconnect\n", s->client[pos].id_socket);
    
    new_max_socket = -1;
    
    /* Seek new socket max */
    if ( s->max_socket == s->client[pos].id_socket ) {
        for ( i = 0; i < s->nb_leach; i++) {
            if ( i != pos 
                && (s->client[i]).id_socket > new_max_socket ) {
                
                new_max_socket = (s->client[i]).id_socket;
            }
        }
    }

    closesocket((s->client[pos]).id_socket);
    
    /* Move memory to avoid blank into array */
    memmove(s->client + pos, s->client + pos + 1, (s->nb_leach - pos - 1) * sizeof(Client));  
    
    s->max_socket = (new_max_socket == -1 ) ? s->max_socket : new_max_socket;
    --(s->nb_leach);
    
    return;
}

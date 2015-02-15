//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "error.h"
#include "collectors.h"
#include "tcp.h"


Collector* newCollect(int nb_vol) {
    Collector* collect;
    
    if ( (collect = calloc(1, sizeof(*collect))) == NULL) {
        QUIT_MSG("Can't Allocate Collector");
    }
        
    if ((collect->volumes = calloc(nb_vol, sizeof(char))) == NULL) {
        QUIT_MSG("Can't Allocate Collector's volume list");
    }
        
    return collect;
}

void freeCollect(Collector *coll) {
    free(coll->volumes);

}

Collector acceptCollector( int const server_socket ) {
    Collector new_client;
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

Collector** collectorsFromIps(int nb_coll, char** ips){
    int i;
    Collector* coll_list[nb_coll];
    struct hostent *h;

    for (i = 0; i < nb_coll; ++i){
        if ((coll_list[i] = calloc(1, sizeof *coll_list[i])) == NULL) {
            QUIT_MSG("Can't Allocate Collector n°%d", i);
        }
    }
    
    for (i = 0; i < nb_coll; ++i){
        /*
        if( (h = gethostbyname(ips[i])) == NULL ) {
            QUIT_MSG("Can't Connect to Collector n°%d", i);
        }
        else {
            memcpy(&coll_list[i].sock.ip, h->h_addr, h->h_length);
        }
        
        (coll_list[i].sock).port = COLLECT_PORT;
        tcpStart(coll_list[i]->sock);
        askVolList(coll_list[i]);
        */
    }
    
    return NULL;
}

void askVolList(Collector* collect) {
    char data[50];
    (void) data;
    tcpAction(collect->sock, "ListOfVolumes", 13, SEND);
}

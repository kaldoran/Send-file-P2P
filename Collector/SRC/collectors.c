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
        QUIT_MSG("Can't Allocate Collector : ");
    }
        
    if ((collect->volumes = calloc(nb_vol, sizeof(char))) == NULL) {
        QUIT_MSG("Can't Allocate Collector's volume list : ");
    }
        
    return collect;
}

void freeCollect(Collector *coll) {
    if ( coll->volumes != NULL ) {
        free(coll->volumes);
    }
    free(coll);
}

Collector** collectorsFromIps(int nb_coll, char** ips) {
    int i;
    Collector* coll_list[nb_coll];
    struct hostent *h;

    for (i = 0; i < nb_coll; ++i) {
        if ((coll_list[i] = calloc(1, sizeof *coll_list[i])) == NULL) {
            QUIT_MSG("Can't Allocate Collector n°%d", i);
        }
    }
    
    
    for (i = 0; i < nb_coll; ++i) { 
      
        if( (h = gethostbyname(ips[i])) == NULL ) {
            QUIT_MSG("Can't Connect to Collector n°%d", i);
        }
        else {
            memcpy(&coll_list[i]->c.sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
        }
        
        coll_list[i]->c.sock_info.sin_port = COLLECT_PORT;
        tcpStart(coll_list[i]->c);
        askVolList(coll_list[i]);
        
    }
   
    return NULL;
}

void askVolList(Collector* collect) {
    char data[50];
    (void) data;
    tcpAction(collect->c, "ListOfVolumes", 13, SEND);
}

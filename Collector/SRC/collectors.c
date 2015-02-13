//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "collectors.h"
#include "tcp.h"


Collector* new_collect(int nb_vol) {
    Collector* collect;
    
    if ( (collect = calloc(1, sizeof(*collect))) == NULL) {
        QUIT_MSG("Can't Allocate Collector");
    }
        
    if ((collect->volumes = calloc(nb_vol, sizeof(char))) == NULL) {
        QUIT_MSG("Can't Allocate Collector's volume list");
    }
    
    collect->nb_volumes = nb_vol;
    
    return collect;
}

void free_collect(Collector *coll) {
    free_socket(coll->sock);
    free(coll->volumes);

}

Collector** CollectorsFromIps(int nb_coll, char** ips){
    int i;
    Collector* coll_list[nb_coll];
    struct hostent *h;

    for (i = 0; i < nb_coll; ++i){
        if ((coll_list[i] = calloc(1, sizeof *coll_list[i])) == NULL) {
            QUIT_MSG("Can't Allocate Collector n°%d", i);
        }
    }
    
    for (i = 0; i < nb_coll; ++i){
        if( (h = gethostbyname(ips[i])) == NULL ) {
            QUIT_MSG("Can't Connect to Collector n°%d", i);
        }
        else {
            memcpy(&coll_list[i].sock.ip, h->h_addr, h->h_length);
        }
        (coll_list[i].sock).port = COLLECT_PORT;
        tcp_start(coll_list[i].sock);
        ask_vol_list(coll_list[i]);
    }
    
    return NULL;
}

void ask_vol_list(Collector* collect) {
    char data[50];
    (void) data;
    tcp_action(collect->sock, "ListOfVolumes", 13, SEND);
}

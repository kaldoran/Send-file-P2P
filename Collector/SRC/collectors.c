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

void askVolList(Collector* collect, int nb_vol) {
    char data[nb_vol];
    int i;
    (void) data;
    tcpAction(collect->c, "ListOfVolumes", 13, SEND);
    
    tcpAction(collect->c, data, nb_vol, RECEIVED);
    
    switch(data[0]){
        case 'f': memset(collect->volumes[i], '1', nb_vol);
                  break;
        case 'n': memset(collect->volumes[i], '0', nb_vol);
                  break;
        default: strcpy(collect->volumes, data);
    }
}

//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "tcp.h"
#include "error.h"
#include "socket.h"
#include "collectors.h"


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
    tcpAction(collect->c, "ListOfVolumes", 13, SEND);
    
    tcpAction(collect->c, data, nb_vol, RECEIVED);
    
    switch(*data){
        case 'f': memset(collect->volumes, '1', nb_vol);
                  break;
        case 'n': memset(collect->volumes, '0', nb_vol);
                  break;
        default: strcpy(collect->volumes, data);
    }
}

int* findCollVol(Index* index, Collector** coll_list, int nb_seed){
    int i,j;
    
    int* collVol = NULL;
    
    if ( (collVol = malloc(2*sizeof(int))) == NULL ) {
        QUIT_MSG("Can't allocate collVol : ");
    }
    
    collVol[0] = -1;
    collVol[1] = -1;
    
    for(i = 0; i < nb_seed; ++i){
        for(j = 0; j < index->nb_package; ++j){
            if(coll_list[i]->volumes[j] == 1 && index->local_vols[j] == 0){
                collVol[0] = i;
                collVol[1] = j;
                return collVol;
            }
        }
    }
    
    return collVol;
}

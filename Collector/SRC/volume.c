//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.c                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collectors_list.h"
#include "verification.h"
#include "collectors.h"
#include "volume.h"
#include "error.h"
#include "tcp.h"

void getVolume(Index* index, Collector** collectors_list, int nb_seed, FILE* file) {
    unsigned char read[index->pack_size];
    int* collVol;

    collVol = findCollVol(index, collectors_list, nb_seed);
    char vol[10] = "";  /* 10 carac : 3 for "Vol", and 7 left for the number (i.e 9 millions person ) */

    sprintf(vol, "Vol%d", collVol[1]);
    
    tcpAction(collectors_list[collVol[0]]->c, vol, sizeof(vol), SEND);

    tcpAction(collectors_list[collVol[0]]->c, read, index->pack_size, RECEIVED);

    if(checkVol(index, read, collVol[1])) {
    
        index->local_vols[collVol[1]] = 1;
        
        fseek(file, (index->pack_size * collVol[1] ), SEEK_SET);
        rewind(file);
        
        fprintf(file, "%s", read);
 
    } else {
        printf("Wrong volume %d",collVol[1]);
    }
    
    free(collVol);
}

void sendVolume(Client c, int vol_num, int vol_size, FILE* file) {
    char buf[vol_size];
    
    fseek(file, ( vol_size * vol_num ), SEEK_SET);
    
    if(fread ((char*)buf, vol_size, 1, file) == 0){
        DEBUG_MSG("[ERROR] sending empty volume\n");
    }
       
    tcpAction(c, buf, vol_size, SEND);
}

void sendListVolumes(Client c, Index* index) {
    tcpAction(c, index->local_vols, index->nb_package, SEND);
}

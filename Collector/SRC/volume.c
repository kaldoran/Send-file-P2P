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
#include "message.h"
#include "volume.h"
#include "error.h"
#include "tcp.h"

bool getVolume(Index* index, Collector** collectors_list, Server* s) {
    unsigned char read[index->pack_size];
    int* collVol;

    collVol = findCollVol(index, collectors_list, s->nb_seed);
    
    if ( collVol[0] == -1 ) {
        freeCollectorsList(collectors_list, s->nb_seed);
        collectors_list = fillCollectorsList(s, index);
        
        return FALSE;
    }
    
    char vol[sizeof(PREFIX_OF_VOLUME_MSG) + 5] = "";

    sprintf(vol, "%s%d", PREFIX_OF_VOLUME_MSG, collVol[1]);
    
    tcpAction(collectors_list[collVol[0]]->c, vol, sizeof(vol), SEND);

    tcpAction(collectors_list[collVol[0]]->c, read, index->pack_size, RECEIVED);

    if(checkVol(index, read, collVol[1])) {
    
        index->local_vols[collVol[1]] = 1;
        
        fseek(s->file, (index->pack_size * collVol[1] ), SEEK_SET);
        rewind(s->file);
        
        fprintf(s->file, "%s", read);
 
        return isComplet(index->local_vols);
    } else {
        printf("Wrong volume %d",collVol[1]);
    }
    
    free(collVol);
    return FALSE;
}

void sendVolume(Client c, int vol_num, int vol_size, FILE* file) {
    char buf[vol_size];
    
    fseek(file, ( vol_size * vol_num ), SEEK_SET);
    
    if(fread ((char*)buf, vol_size, 1, file) == 0){
        DEBUG_MSG("[ERROR] sending empty volume.");
    }
       
    tcpAction(c, buf, vol_size, SEND);
}

void sendListVolumes(Client c, Index* index) {
    tcpAction(c, index->local_vols, index->nb_package, SEND);
}

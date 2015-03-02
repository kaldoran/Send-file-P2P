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
    int nb_useless_coll = 0;
    int lim_useless_coll = s->nb_seed/4;
    int num_vol = -1;
    int i;
    
    for(i = 0; i < s->nb_seed; ++i){
        num_vol = findCollVol(index, collectors_list[i]);
        
        if ( num_vol == -1 ) {
            nb_useless_coll ++;
            if(nb_useless_coll > lim_useless_coll){
                freeCollectorsList(collectors_list, s->nb_seed);
                collectors_list = fillCollectorsList(s, index);
                
                return isComplet(index->local_vols);
            }
        } else {
            char vol[sizeof(PREFIX_OF_VOLUME_MSG) + 5] = "";

            sprintf(vol, "%s%d", PREFIX_OF_VOLUME_MSG, num_vol);
            
            tcpAction(collectors_list[i]->c, vol, sizeof(vol), SEND);

            tcpAction(collectors_list[i]->c, read, index->pack_size, RECEIVED);

            if(checkVol(index, read, num_vol)) {
            
                index->local_vols[num_vol] = 1;
                
                fseek(s->file, (index->pack_size * num_vol ), SEEK_SET);
                rewind(s->file);
                
                fprintf(s->file, "%s", read);
            } else {
                printf("Wrong volume %d",num_vol);
            }
        }
    }
    return isComplet(index->local_vols);
}

int findCollVol(Index* index, Collector* coll){
    int num_vol;
    
    for(num_vol = 0; num_vol < index->nb_package; ++num_vol){
        if(coll->volumes[num_vol] == 1 && index->local_vols[num_vol] == 0){
            return num_vol;
        }
    }
    
    return -1;
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

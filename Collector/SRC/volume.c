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

void sendVolume(Client c, int vol_num, int vol_size, FILE* file) {
    char buf[vol_size];
    memset(buf, '\0', vol_size);
    
    fseek(file, ( vol_size * vol_num ), SEEK_SET);
    
    if(fread ((char*)buf, vol_size, 1, file) == 0){
        DEBUG_MSG("[ERROR] sending empty volume.");
    }
       
    tcpAction(c, buf, vol_size, SEND);
}

bool getVolume(Index* index, Collector** collectors_list, Server* s) {
    unsigned char read[index->pack_size];
    int nb_useless_coll = 0;
    int lim_useless_coll = s->nb_seed/4;
    int num_vol = -1;
    int i;
    
    for(i = 0; i < s->nb_seed; ++i) {
        num_vol = findCollVol(index, collectors_list[i]);
        
        if ( num_vol == -1 ) {
            nb_useless_coll++;
            
            if(nb_useless_coll > lim_useless_coll) {
                freeCollectorsList(collectors_list, s->nb_seed);
                collectors_list = fillCollectorsList(s, index);
            }
        } else {
            char vol[sizeof(PREFIX_OF_VOLUME_MSG) + 5] = "";

            printf("[INFO] Ask volume %d to Client %d\n", num_vol, collectors_list[i]->c.id_socket);
            sprintf(vol, "%s%d", PREFIX_OF_VOLUME_MSG, num_vol);
            
            tcpAction(collectors_list[i]->c, vol, sizeof(vol), SEND);

            if ( tcpActionDelay(collectors_list[i]->c, read, index->pack_size, S_DELAY, MS_DELAY) < 0 ) {
                printf("[ERROR] Client %d does not send information in time\n", collectors_list[i]->c.id_socket);
                nb_useless_coll++;
                
                if(nb_useless_coll > lim_useless_coll) {
                    freeCollectorsList(collectors_list, s->nb_seed);
                    collectors_list = fillCollectorsList(s, index);
                    return FALSE;
                }
            } else {
                if(checkVol(index, read, num_vol)) {
                    
                    fseek(s->file, (index->pack_size * num_vol ), SEEK_SET);
                    rewind(s->file);
                    
                    fprintf(s->file, "%s", read);
                } else {
                    printf("[ERROR] Wrong volume %d received\n", num_vol);
                }
            }
        }
    }
    
    return isComplet(index->local_vols);
}

int findCollVol(Index* index, Collector* coll){
    int num_vol;
    
    for(num_vol = 0; num_vol < index->nb_package; ++num_vol){
        if(coll->volumes[num_vol] == 1 && index->local_vols[num_vol] == 0) {
            return num_vol;
        }
    }
    
    return -1;
}

void askVolList(Collector* collect, int nb_vol) {
    char data[nb_vol];
    
    printf("[INFO] Ask the list of volume to %d\n", collect->c.id_socket);
    tcpAction(collect->c, LIST_OF_VOLUMES_MSG, sizeof(LIST_OF_VOLUMES_MSG), SEND);
    
    if ( tcpActionDelay(collect->c, data, nb_vol, S_DELAY, MS_DELAY) < 0 ) {
        printf("[ERROR] Client %d does not send information in time\n", collect->c.id_socket);
        
        memset(collect->volumes, '0', nb_vol);
    } else {
        removeEndCarac(data);
        printf("Received : %s\n", data);
        
        if ( *data == *FULL_VOLUME_MSG) {
            printf("[INFO] %d got them all\n", collect->c.id_socket);
            memset(collect->volumes, '1', nb_vol);
        } else if ( *data == *NONE_VOLUME_MSG ) {
            printf("[INFO] %d got no volume\n", collect->c.id_socket);
            memset(collect->volumes, '0', nb_vol);
        } else {
            printf("[INFO] %d got partial volume\n", collect->c.id_socket);
            strcpy(collect->volumes, data);
        }
    }

    return;
}

void sendListVolumes(Client c, Index* index) {
    int i;
    
    for ( i = 1; i < index->nb_package; i++ ) {
        if ( index->local_vols[0] != index->local_vols[i] ) {
            tcpAction(c, index->local_vols, index->nb_package, SEND);
            return;
        }
    }
    
    if ( index->local_vols[0] == '1' ) {
        tcpAction(c, FULL_VOLUME_MSG, sizeof(FULL_VOLUME_MSG), SEND);
    } else {
        tcpAction(c, NONE_VOLUME_MSG, sizeof(NONE_VOLUME_MSG), SEND);
    }
    
    return;
}

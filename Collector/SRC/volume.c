//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.c                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>

#include "verification.c"
#include "collectors.h"
#include "volume.h"
#include "tcp.h"

void getVolume(Index* index, Collector** collectors_list, int nb_seed, FILE* file) {
    char read[index->pack_size];
    int* collVol;
    int id_vol;

    collVol = findCollVol(index, collectors, nb_seed);
    char* vol = strcat("Vol", itoa(collVol[1], NULL, 10));

    tcpAction(collectors_list[collVol[0]]->c, vol, sizeof(vol), SEND);

    tcpAction(collector, read, index->pack_size, RECEIVED);

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
    fread ((char*)buf, vol_size, 1, file);
       
    tcpAction(c, buf, vol_size, SEND);
}

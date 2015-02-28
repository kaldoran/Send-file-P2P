//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : verification.c                                 |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "verification.h"

void hexToString(unsigned char outbuf[SHA_DIGEST_LENGTH], char outsha[40]) {
    int i;
    
    for ( i = 0; i < SHA_DIGEST_LENGTH; i++) {
         sprintf( outsha + i * 2, "%02x", outbuf[i]);
    }
}

bool checkFile(FILE* file, Index* index) {
    bool full = TRUE;

    int i;
    unsigned char inbuf[index->pack_size];
    
    for ( i = 0; i < index->nb_package; i++ ) {
        memset(inbuf, '\0', index->pack_size); 
        
        if(fread ((char*)inbuf, index->pack_size, 1, file) == 0){
            full = FALSE;
            index->local_vols[i] = '0';
        }
        else if(!checkVol(index, inbuf, i)){
            full = FALSE;
        }
    }

    return full;
}

bool checkVol(Index* index, unsigned char* vol, int id_vol) {
    char outsha[40];
    unsigned char outbuf[SHA_DIGEST_LENGTH];

    SHA1(vol, sizeof(vol), outbuf);

    hexToString(outbuf, outsha);
    
    if ( strcmp(outsha, index->sha[id_vol]) == 0 ) {
        printf("Volume %i is the same.\n", id_vol);
        
        index->local_vols[id_vol] = '1';
        return TRUE;
    }
    
    index->local_vols[id_vol] = '0';
    return FALSE;
}

bool fileExist(const char *filename) {
    return access( filename, R_OK|W_OK ) != -1;
}

bool isComplet(const char* vol) {

    for ( ; *s != '\0'; s++ ) {
        if ( *s == 0 ) {
            return FALSE;
        }
    }
    
    return TRUE;
}

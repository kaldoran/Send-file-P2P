//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : verification.c                                 |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

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
        
        fread ((char*)inbuf, index->pack_size, 1, file);
        
        if(!checkVol(index, inbuf, i)){
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

    printf("%s\n", outsha);
    printf("%s\n", index->sha[id_vol]);
    
    if ( strcmp(outsha, index->sha[id_vol]) == 0 ) {
        printf("Volume %i is the same.\n", id_vol);
        return TRUE;
    }
    
    return FALSE;
}

bool fileExist(const char *filename) {
    return access( filename, R_OK|W_OK ) == -1;
}
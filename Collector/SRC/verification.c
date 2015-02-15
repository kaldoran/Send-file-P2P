//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : verification.c                                 |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verification.h"

void hexToString(unsigned char outbuf[SHA_DIGEST_LENGTH], char outsha[40]) {
    int i;
    
    for ( i = 0; i < SHA_DIGEST_LENGTH; i++) {
         sprintf( outsha + i * 2, "%02x", outbuf[i]);
    }
}

void checkFile(FILE* file, Index* index) {
    
    int i;
    char outsha[40];
    unsigned char inbuf[index->pack_size];
    unsigned char outbuf[SHA_DIGEST_LENGTH];
    

    for ( i = 1; i <= index->pack_size; i++ ) {
        memset(outbuf, '\0', SHA_DIGEST_LENGTH);
        memset(inbuf, '\0', index->pack_size); 
        
        fread ((char*)inbuf, index->pack_size, 1, file);
        SHA1(inbuf, sizeof(inbuf), outbuf);

        hexToString(outbuf, outsha);

        printf("%s\n", outsha);
        printf("%s\n", index->sha[i-1]);
        if ( strcmp(outsha, index->sha[i-1]) == 0 ) {
            printf("Index %i is the same.\n", i);
        
        }
    }

    return;
}
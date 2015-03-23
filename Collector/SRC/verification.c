//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : verification.c                                 |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

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

        if( !checkVol(index, inbuf, sizeof(inbuf), i)) {
            printf("\t - Some volumes are missing\n");
            full = FALSE;
        }
    }

    if ( full ) {
        printf("\t - we've got all volume\n");
    }
    return full;
}

bool checkVol(Index* index, unsigned char* vol, int vol_size, int id_vol) {
    char outsha[40];
    unsigned char outbuf[SHA_DIGEST_LENGTH];
    SHA1(vol, vol_size, outbuf);

    hexToString(outbuf, outsha);
    if ( strcmp(outsha, index->sha[id_vol]) == 0 ) {        
        index->local_vols[id_vol] = '1';
        return TRUE;
    }
    
    index->local_vols[id_vol] = '0';
    return FALSE;
}

bool fileExist(const char* filename) {
    struct stat s;
    
    if ( stat(filename, &s) == -1 ) {
        printf("[ERROR] '%s' does not exist.\n", filename);
        return FALSE;
    }
    
    if ( s.st_mode & S_IFDIR ) {
        printf("[ERROR] '%s' is a directory.\n", filename);
        return FALSE;
    }

    return TRUE;
}

bool verifPort(int port) {

    if(port <= 1024){
        printf("[ERROR] The port must be greater than 1024.\n");
        return FALSE;
    }

    if(port > 65536) {
        printf("[ERROR] The port must be lower than 65536.\n");
        return FALSE;
    }

    return TRUE;
}


bool isComplet(const char* vol) {

    for ( ; *vol != '\0'; vol++ ) {
        if ( *vol == 0 ) {
            return FALSE;
        }
    }
    
    return TRUE;
}

//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : intout.c                                       |
// DATE : 03/03/15                                          |
//----------------------------------------------------------

#include "error.h"
#include "inout.h"
#include "verification.h"

char* askNDex() {
    char* file;
    
    if ( (file = calloc(FILENAME_MAX, sizeof(char))) == NULL ) {
        QUIT_MSG("Can't allocate file");
    }
    
    do {
        printf("\nWhich .ndex do you want to use ?\n");

        if(scanf("%s", file) != 1) {
            DEBUG_MSG("Nothing read when asking index.");
        }

        emptyBuffer();
    } while ( !fileExist(file) );
    
    return file;
}


int askPort() {
    int port;
    
    do {
        printf("\n[Q] On which port do you want to start the collector ?\n");

        if(scanf("%d", &port) != 1){
            DEBUG_MSG("Nothing read when asking port.");
        }

        emptyBuffer();
    } while ( !verifPort(port) );
    
    return port;
}

void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    
    return;
}

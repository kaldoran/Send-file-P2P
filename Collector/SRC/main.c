//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "collectors.h"

#include "windows.h"


void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}

void verifications(int argc, char const *argv[]) {
    if ( argc < 2 ) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
        
    if( access( argv[1], R_OK|W_OK ) == -1 ) {
        QUIT_MSG("can't acces to : '%s' : ", argv[1]);
    }
}

int main(int argc, char const *argv[]) {
    verifications(argc, argv);
    
    initWindows();
    
    startCollector(argv[1]);
    
    endWindows();
    
    exit(EXIT_SUCCESS);
}

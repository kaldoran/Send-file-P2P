//----------------------------------------------------------
// AUTHOR : REYNAUD Nicolas                                 |
// FILE : main.c                                            |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

#include "inout.h"
#include "file.h"

void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}


int main(int argc, char const *argv[]) {
    char* ip;
    int port;
    int volSize;
    
    printf("[[INFO] Generateur] Welcome to this awesome new project\n");
    
    if ( argc < 2 ) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    
    ip = askBossIp();
    port = askBossPort();
    volSize = askVolSize();
    volSize *= 1000;
    createNDex(ip, port, volSize, (char *)argv[1]);
    
    free(ip);
   
    exit(EXIT_SUCCESS);
}

//----------------------------------------------------------
// AUTHOR : REYNAUD Nicolas                                 |
// FILE : main.c                                            |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "error.h"
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
    struct stat buf;
     
    printf("[INFO] Welcome to this awesome Generator\n\n");
    
    if ( argc < 2 ) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    
    if ( stat(argv[1], &buf) == -1 ) {
        QUIT_MSG("Can't stats '%s' : ", argv[1]);
    }
    
    if ( buf.st_size == 0 ) {
        printf("[WARNING] '%s' is an empty file.\n\n", argv[1]);
    }
    
    ip = askBossIp();
    port = askBossPort();
    volSize = askVolSize();
    volSize *= 1000;
    createNDex(ip, port, volSize, (char *)argv[1], buf);
    
    free(ip);
   
    exit(EXIT_SUCCESS);
}

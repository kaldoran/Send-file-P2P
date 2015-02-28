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

int main() {
    char* ip;
    char* file;
    int port;
    int volSize;
    struct stat buf;
     
    printf("[INFO] Welcome to this awesome Generator\n\n");
        
    file = askFile();
    
    if ( stat(file, &buf) == -1 ) {
        QUIT_MSG("Can't stats '%s' : ", file);
    }
    
    if ( buf.st_size == 0 ) {
        printf("[WARNING] '%s' is an empty file.\n\n", file);
    }
    

    ip = askBossIp();
    port = askBossPort();
    volSize = askVolSize();
    volSize *= 1000;
    createNDex(ip, port, volSize, file, buf);
    
    free(ip);
    free(file);
   
    exit(EXIT_SUCCESS);
}

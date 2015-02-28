//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "verification.h"
#include "collectors.h"

#include "windows.h"


void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}


char* askNDex() {
    char* file;
    
    do {
        printf("Which .ndex do you want to use ? ");
        scanf("%ms", &file);
    } while ( !fileExist(file) );
    
    return file;
}


int askPort() {
    int port;
    
    do {
        printf("On which port do you want to start the collector ? ");
        scanf("%d", &port);
    } while (port < 1024 && port > 65536 );
    
    return port;
}

int main() {

    initWindows();

    startCollector(askNDex(), askPort());
    
    endWindows();
    
    exit(EXIT_SUCCESS);
}

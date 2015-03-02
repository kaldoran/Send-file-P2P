//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : inout.c                                            |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"
#include "verification.h"
#include "inout.h"

char* askBossIp() {
    char* ip;
    int verif;
    
    if ( (ip = calloc(15, sizeof(char))) == NULL ) {
        QUIT_MSG("Can't alloc ip");
    } 

    do {
        printf("What is the IP adress of the boss ?\n");
        verif = scanf("%15[^\n]",ip);
        emptyBuffer();
    } while(verif != 1 || !verifBossIp(ip));

    return ip;
}


int askBossPort() {
    int port ,verif;

    do {
        printf("What is the port to connect to ?\n");
        printf("(From 1024 to 65536)\n");
        verif = scanf("%d",&port);
        emptyBuffer();
    } while(verif != 1 || !verifBossPort(port));

    return port;
}


int askVolSize() {
    int size ,verif;

    do {
        printf("What size do you want the volumes to be ?\n");
        printf("(Size in ko from 8 to 64, both included)\n");
        verif = scanf("%d",&size);
        emptyBuffer();
    } while(verif != 1 || !verifVolSize(size));

    return size;
}

char* askFile() {
    int verif;
    char* file;
    
    if ( (file = calloc(FILENAME_MAX, sizeof(char))) == NULL ) {
        QUIT_MSG("Can't allocate file");
    }
    
    
    do {
        printf("On which file do you want to create the '.ndex' file ?\n");
        verif = scanf("%s", file);
    } while(verif != 1 || access(file ,R_OK|W_OK ) == -1);

    return file;
}

void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    
    return;
}

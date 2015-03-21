//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : intout.c                                       |
// DATE : 03/03/15                                          |
//----------------------------------------------------------


#include "error.h"
#include "inout.h"
#include "stdio.h"
#include "libgen.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
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

char* askShareRepo() {
    char* repo;
    
    if ( (repo = calloc(FILENAME_MAX, sizeof(char))) == NULL ) {
        QUIT_MSG("Can't allocate file");
    }
    
    printf("\nWhat is your sharing repository ?\n");
    while(scanf("%s", repo) != 1) {
        DEBUG_MSG("Nothing read when asking sharing repository.");
    }

    emptyBuffer();
    mkdirRec(repo);
    
    return repo;
}

void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    
    return;
}

void mkdirRec(char *dir) {
    char *token;
    token = strtok(dir, "/");
    while ( token != NULL ) {
        #ifdef linux
            mkdir(token, 0777);
        #else
            __mkdir(token);
        #endif
        chdir(token);
        token = strtok(NULL, "/");
    }
    
    return;
}

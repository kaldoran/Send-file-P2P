//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : intout.c                                       |
// DATE : 03/03/15                                          |
//----------------------------------------------------------

#include <sys/stat.h>

#include "error.h"
#include "inout.h"
#include "string.h"
#include "verification.h"
#include "configuration.h"

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

char *askShareRepo() {
    char* repo;
    
    #ifndef SHARING_PATH
        
   
        if ( (repo = calloc(FILENAME_MAX, sizeof(char))) == NULL ) {
            QUIT_MSG("Can't allocate file");
        }
        
        printf("\n[Q] What is your sharing repository ? [Be carefull, if it doesn't exists we'll create it !]\n");
        while(scanf("%s", repo) != 1) {
            DEBUG_MSG("Nothing read when asking sharing repository.");
        }

        emptyBuffer();
    #else 
        if ( (repo = calloc(sizeof(SHARING_PATH), sizeof(char))) == NULL ) {
            QUIT_MSG("Can't allocate file");
        }
        
        strcpy(repo, SHARING_PATH);
    #endif
    
    return repo;
}

void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
    
    return;
}

void mkdirRec(const char *dir) {
    char cpy_dir[(int)sizeof(dir) + 1 ] = "";
    char *token;
    
    strcpy(cpy_dir, dir);
    token = strtok(cpy_dir, "/");

    while ( token != NULL ) {
        #ifdef linux
            mkdir(token, 0777);
        #else
            _mkdir(token);
        #endif

        if (chdir(token) != 0){
            DEBUG_MSG("Can't change the working directory.");
        }

        token = strtok(NULL, "/");
    }
    
    return;
}

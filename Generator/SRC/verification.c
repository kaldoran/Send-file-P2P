//----------------------------------------------------------
// AUTHOR : BASCOL Kevin & REYNAUD Nicolas                   |
// FILE : verification.c                                     |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "error.h"
#include "verification.h"

bool verifBossIp(char* ip){
    int total = 0;
    char *token;
    int itoken;
    token = strtok(ip, ".");
    while( token != NULL ) {        
        itoken = atoi(token);
        if ( itoken < 0 || itoken > 255 || *ip == '.' ) {
            ERROR_MSG("Ip range for each part is from 0 To 255\n"); 
        }
        
        if ( (token = strtok(NULL, ".")) == NULL && total == 0 ) {
            ERROR_MSG("Ip delimitor is '.'\n");
        }

        ++total;
    }
    
    if ( total != 4) { 
        ERROR_MSG("Ip is normaly composed by 4 part\n"); 
    }
    
    return TRUE;
}

bool verifBossPort(int port) {
    if(port <= 1024){
        ERROR_MSG("The port must be greater than 1024\n");
    }
    else if(port > 65536) {
        ERROR_MSG("The port must be lower than 65536\n");
    }

    return TRUE;
}

bool verifVolSize(int size){
    if(size < 8){
        ERROR_MSG("The volumes' size must be greater than 8ko\n");
    }
    else if(size > 64) {
        ERROR_MSG("The volumes' size must be lower than 64ko\n");
    }

    return TRUE;
}

bool verifFileExist(char* filename) {
    struct stat s;
    if ( stat(filename, &s) == -1 ) {
        ERROR_MSG("'%s' does not exist\n", filename);
    } else if ( s.st_mode & S_IFDIR ) {
        ERROR_MSG("'%s' is a directory\n", filename);
    }

    return TRUE;
}

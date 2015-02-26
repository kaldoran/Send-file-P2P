//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : verification.c                                     |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "verification.h"

bool verifBossIp(char* ip){
    int total = 0;
    char *token;
    int itoken;
    
    token = strtok(ip, ".");
    while(total <= 4 && token != NULL) {
        itoken = atoi(token);
        if ( itoken < 0 || itoken > 255 ) {
            return FALSE;
        }
        
        token = strtok(NULL, ".");
        ++total;
    }
    
    return total == 4;
}

bool verifBossPort(int port) {
    if(port <= 1024){
        printf("[ERROR] : The port must be greater than 1024\n");
    }
    else if(port > 65536) {
        printf("[ERROR] : The port must be lower than 65536\n");
    }
    else {
        return TRUE;
    }
    return FALSE;
}

bool verifVolSize(int size){
    if(size < 8){
        printf("[ERROR] : The volumes' size must be greater than 8ko\n");
    }
    else if(size > 64) {
        printf("[ERROR] : The volumes' size must be lower than 64ko\n");
    }
    else {
        return TRUE;
    }
    return FALSE;
}

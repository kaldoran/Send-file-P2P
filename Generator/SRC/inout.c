//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : inout.c                                            |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#include <stdio.h>
#include "verification.h"


char* askIpBoss() {
    char* ip;

    do {
        printf("What is the IP adress of the boss ?");
        scanf("%15s",&ip);
        emptyBuffer();
    } while(verifIpBoss(ip));
}


int askPortBoss() {	

}


int askSizePack() {	

}

void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

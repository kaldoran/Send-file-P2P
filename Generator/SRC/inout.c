//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : inout.c                                            |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#include <stdio.h>
#include "verification.h"


char* askBossIp() {
    char* ip;

    do {
        printf("What is the IP adress of the boss ?\n");
        scanf("%15s",&ip);
        emptyBuffer();
    } while(verifBossIp(ip));
}


int askBossPort() {
	int port;

	do {
		printf("What is the port to connect to ?\n");
        scanf("%d",&port);
        emptyBuffer();
    } while(verifBossPort(port));
}


int askVolSize() {
	int size;

	do {
		printf("What size do you want the volumes to be ?\n");
        scanf("%d",&size);
        emptyBuffer();
    } while(verifVolSize(size));

}

void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

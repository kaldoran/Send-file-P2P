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
#include "verification.h"

void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}

int main(int argc, char * argv[]) {
    char* ip = NULL;
    char* file = NULL;
    int port = 0;
    int volSize = 0;
    
    printf("[INFO] Welcome to this awesome Generator\n\n");
    
    #ifndef DEBUG
        (void) argv;
    #else 
        if ( argc > 4 ) {
            if ( !verifFileExist(file = argv[1]) 
              || !verifBossIp(ip = argv[2]) 
              || !verifBossPort(port = atoi(argv[3]))
              || !verifVolSize(volSize = atoi(argv[4])) ) {
              
                QUIT_MSG("Reading program argument, please refere to previous error(s)\n"); 
            }
        } else {
            printf("[INFO] Remember, you could use program argument in debug mode. \n");
            printf("\t %s <file> <ip> <port> <volSize>\n", argv[0]);
            printf("\t With <port> between 1024 and 65536.\n");
            printf("\t and <volSize> between 16 and 64\n");
        }
        
        if ( argc <= 4 ) { 
    #endif

            file = askFile();
            ip = askBossIp();
            port = askBossPort();
            volSize = askVolSize();  
    #ifdef DEBUG
        } 
    #endif
    
    volSize *= 1000;
    createNDex(ip, port, volSize, file);
    
    if ( argc <= 4 ) {
        free(ip);
        free(file);
    } 
    
    END();
    exit(EXIT_SUCCESS);
}

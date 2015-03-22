//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------

#include "error.h"
#include "inout.h"
#include "collectors.h"
#include "verification.h"
#include "windows.h"

int main(int argc, char* argv[]) {

    char *nDex = NULL;
    int port = 0;
   
    initWindows();
    
    #ifdef DEBUG
        if ( argc > 2 ) {
            if ( !fileExist(nDex = argv[1]) 
              || !verifPort(port = atoi(argv[2])) ) {
              
                QUIT_MSG("An error occur, please refere to previous error(s)\n");
            }
            mkdirRec(argv[3]);
        } else {
            printf("[INFO] Remember, you could use program argument in debug mode. \n");
            printf("\t %s <ndex> <port> <share_directory>\n", argv[0]);
            printf("\t With <port> between 1024 and 65536.\n");
        }
    #else
        (void) argv;
    #endif
    
    if ( argc < 3 ) {
        nDex = askNDex();
        port = askPort();
        askShareRepo(); /* These ask, and move to the repository */
    }
    
    startCollector(nDex, port);
    
    if (  argc < 3 ) {
        free(nDex);
    }
    
    endWindows();
    
    END();
    exit(EXIT_SUCCESS);
}

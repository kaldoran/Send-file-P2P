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
    char *sharing_path = NULL;
    int port = 0;
   
    initWindows();
    
    #ifndef DEBUG
        (void) argv;
    #else
        if ( argc > 3 ) {
            if ( !fileExist(nDex = argv[1]) 
              || !verifPort(port = atoi(argv[2])) ) {
              
                QUIT_MSG("An error occur, please refere to previous error(s)\n");
            }
            sharing_path = argv[3];
        } else {
            printf("[INFO] Remember, you could use program argument in debug mode. \n");
            printf("\t %s <path_to_ndex> <port> <share_directory>\n", argv[0]);
            printf("\t With <port> between 1024 and 65536.\n");
        }
        
        if ( argc <= 3 ) {
    #endif
            nDex = askNDex();
            port = askPort();
            sharing_path = askShareRepo(); /* These ask, and move to the repository */
    #ifdef DEBUG
        }
    #endif
    
    startCollector(nDex, port, sharing_path);
    
    if (  argc < 3 ) {
        free(nDex);
        free(sharing_path);
    }
    
    endWindows();
    
    END();
    exit(EXIT_SUCCESS);
}

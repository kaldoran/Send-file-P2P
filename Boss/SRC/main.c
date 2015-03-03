//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <time.h>

#include "error.h"
#include "server.h"
#include "windows.h"

int main() {
    srand(time(NULL));
    
    initWindows();  
    
    startServer();  /* infinit loop into startServer() */
    endWindows();
    
    END();
    exit(EXIT_SUCCESS);
}

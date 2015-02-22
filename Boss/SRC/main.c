//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "server.h"
#include "windows.h"

int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);

    srand(time(NULL));
    
    initWindows();  
    
    startServer();  /* infinit loop into startServer() */
    endWindows();
    
    exit(EXIT_SUCCESS);
}

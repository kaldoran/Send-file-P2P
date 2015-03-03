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

int main() {
    srand(time(NULL));
    
    initWindows();  
    
    startServer();  /* infinit loop into startServer() */
    endWindows();
    
    exit(EXIT_SUCCESS);
}

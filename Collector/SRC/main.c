//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------

#include "error.h"
#include "inout.h"
#include "collectors.h"
#include "windows.h"

int main() {

    initWindows();
    
    askShareRepo();

    startCollector(askNDex(), askPort());

    endWindows();
    
    END();
    exit(EXIT_SUCCESS);
}

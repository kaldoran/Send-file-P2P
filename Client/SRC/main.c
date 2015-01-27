//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For fork and kill


int main(int argc, char const *argv[]) {
    (void)(argc);
    (void)(argv);

    printf("[[INFO] Client] Welcome to this awesome new project\n");
    
    exit(EXIT_SUCCESS);
}

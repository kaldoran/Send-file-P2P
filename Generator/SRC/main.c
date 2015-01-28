//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void usage(const char *name) {
	
	printf("Usage : %s file\n", name);
	
	return;
}


int main(int argc, char const *argv[]) {

    printf("[[INFO] Generateur] Welcome to this awesome new project\n");
    
	if ( argc < 2 ) {
		usage(argv[0]);
		exit(EXIT_SUCCESS);
	}

    createNDex("127.0.0.1", 42000, 16000, (char *)argv[1]);
   
    exit(EXIT_SUCCESS);
}

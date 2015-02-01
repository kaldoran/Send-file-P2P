//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For fork and kill

#include "boolean.h"
#include "struct_index.h"
#include "index_loader.h"

void usage(const char *name) {
	
	printf("Usage : %s file\n", name);
	
	return;
}


int main(int argc, char const *argv[]) {

    
    if ( argc < 2 ) {
		usage(argv[0]);
		exit(EXIT_SUCCESS);
	}

    Index *index = new_index();
	if ( charger_index(argv[1], index) == FALSE ) {
		printf("[ERROR] : Can't connect to boss serveur\n" );
	}
    printf("[[INFO] Client] Welcome to this awesome new project\n");
    
    free_index(index);
    
    exit(EXIT_SUCCESS);
}

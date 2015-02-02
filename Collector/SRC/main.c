//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For fork and kill
#include <openssl/sha.h>
#include <string.h>

#include "boolean.h"
#include "struct_index.h"
#include "index_loader.h"
#include "tcp.h"

void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}

void checkFile(FILE* file, Index* index) {
    
    unsigned char inbuf[index->packSize];
    unsigned char outbuf[SHA_DIGEST_LENGTH];
        
    for ( i = 1; i <= index->nbPackage; i++ ) {
        if ( fgets ((char*)inbuf, index->packSize, file) != NULL ) {
            SHA1(inbuf, sizeof(inbuf), outbuf);
            
            if ( strcmp(outbuf, index->sha[i]) == 0 ) {
                printf("Same\n");
            }
        }
    }

    return;
}

int main(int argc, char const *argv[]) {

    char read[50];
    int nbCollector, i;
    FILE *file = NULL;
    
    if ( argc < 2 ) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    Index *index = new_index();
    if ( charger_index(argv[1], index) == FALSE ) {
        printf("[ERROR] : Can't connect to boss serveur\n" );
    }
    
    new_socket(index);
    tcp_start(index);
    
    tcp_action(index, "List", 4, SEND);
    
    tcp_action(index, read, 50, RECEIVED);
    
    nbCollector = atoi(read);
    for ( i = 0; i < nbCollector; i++ ) {
        printf("Read %d collector information and connect to them, add this to select\n", i);
    }
    if( access( index->file, R_OK|W_OK ) != -1 ) {
        printf("File exist\n Check integrity\n");   
        checkFile(file, index);
    }
    else {
        file = fopen(index->file, "a+");
        for ( i = 0; i < index->fileSize; i++ ) {
            fprintf(file, "#");
        }        
    }
    /** 
     * Same code as Boss but before we need to connect to the N other collecteur 
     *  and ask which part they've got 
     */
    
    printf("[[INFO] Client] Welcome to this awesome new project\n");
    
    free_index(index);
    
    exit(EXIT_SUCCESS);
}

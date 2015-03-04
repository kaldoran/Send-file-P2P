//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : message.c                                      |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "boolean.h"
#include "message.h"

void removeEndCarac(char *input) {
    char *ret;
    
    if((ret = strchr(input, '\r')) != NULL) *ret = '\0'; 
    if((ret = strchr(input, '\n')) != NULL) *ret = '\0';
    
    return;
}


bool handlerUserInput(blockGroup* block_group) {
    int i, j;
    char input[20];
    char* commands[] = { "help", "kick", "total", "socket" };
    
    read(STDIN_FILENO, input, 20);
    removeEndCarac(input);

    if ( strcmp(commands[0], input) == 0 ) {
        printf("Help !\n");
    } 
    else if ( strcmp(commands[1], input) == 0 ) {
        printf("Kick ! \n");
    }
    else if ( strcmp(commands[2], input) == 0 ) {
        printf("Total ! \n");
    } 
    else if ( strcmp(commands[3], input) == 0 ) {
        printf("Socket ! \n");
    }
    
    return FALSE;
}
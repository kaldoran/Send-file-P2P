//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : message.c                                      |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#include <string.h>

#include "message.h"

void removeEndCarac(char *input) {
    char *ret;
    
    if((ret = strchr(input, '\r')) != NULL) *ret = '\0'; 
    if((ret = strchr(input, '\n')) != NULL) *ret = '\0';
    
    return;
}

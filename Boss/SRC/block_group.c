//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : block_group.c                                  |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>

#include "error.h"
#include "group.h"

#include "block_group.h"

blockGroup* newBlockGroup() {

    blockGroup* block_group;
    
    if ( (block_group = calloc(1, sizeof(*block_group))) == NULL ) {
        QUIT_MSG("Can't allocate memory for block group : ");
    }
    
    if ( (block_group->groups = calloc(MAX_GROUP, sizeof(block_group->groups))) == NULL ) {
        QUIT_MSG("Can't allocate memory for block group of group : ");
    }
    
    return block_group;
}

void freeBlockGroup(blockGroup* block_group) {
    int i; 
    
    for ( i = 0; i < block_group->total; i++ ) {
        freeGroup(block_group->groups[i]);
    }
    free(block_group->groups);
    free(block_group);
}
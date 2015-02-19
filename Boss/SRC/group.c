//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : group.c                                        |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "group.h"
#include "client.h"

Group* newGroup(char* const filename) {
    Group* group;
    
    if ( (group = calloc(1, sizeof(*group))) == NULL ) {
        QUIT_MSG("Can't allocate memory for group : ");
    }
    
    if ( (group->checker = calloc(MAX_CONNEXION, sizeof(char))) == NULL ) {
        QUIT_MSG("Can't allocate memory for checkers : ");
    }
    
    group->client = newClientArray(MAX_CONNEXION);
    
    strcpy(group->filename, filename);
    
    return group;
}

void freeGroup(Group* group) {

    freeClientArray(group->client);
    
    free(group->checker); 
    
    free(group);
}

int addGroup( blockGroup* block_group, char* const filename ) {
    int pos;
    
    if ( (pos = existGroup( block_group, filename )) == -1 ) {
        if ( block_group->total == MAX_GROUP ) {
            printf("Can't Create another group \n");
            return -1;
        } 
        
        DEBUG_MSG("Add another group for %s\n", filename);
        
        pos = block_group->total;
        block_group->groups[block_group->total] = newGroup(filename);
        ++block_group->total;

    }
    
    return pos;
}

void removeGroup( blockGroup* block_group, int pos ) {
    DEBUG_MSG("Remove group for %s\n", block_group->groups[pos]->name);
    
    freeGroup(block_group->groups[pos]);

    --block_group->total;
}

int existGroup( blockGroup* block_group, char* const filename ) {
    int i; 
    
    for ( i = 0; i < block_group->total; i++ ) {
        if ( strcmp(block_group->groups[i]->name, filename) == 0 ) {
            return i;
        }
    }
    
    return -1;

}
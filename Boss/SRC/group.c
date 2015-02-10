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
    
    group->client = newClient(MAX_CONNEXION);
    
    strcpy(group->name, filename);
    
    return group;
}

void freeGroup(Group* group) {

    freeClient(group->client);
    
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

int existGroup( blockGroup* block_group, char* const filename ) {
    int i; 
    
    for ( i = 0; i < block_group->total; i++ ) {
        if ( strcmp(block_group->groups[i]->name, filename) ) {
            return i;
        }
    }
    
    return -1;

}
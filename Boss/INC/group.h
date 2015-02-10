//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : group.h                                        |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#include "boolean.h"
#include "struct_group.h"
#include "struct_block_group.h"

#ifndef GROUP_H
#define GROUP_H

Group* newGroup(char* const filename);

void freeGroup(Group* group);

bool addGroup( blockGroup* block_group, char* const filename );

int existGroup( blockGroup* block_group, char* const filename );

#endif /* GROUP_H included */
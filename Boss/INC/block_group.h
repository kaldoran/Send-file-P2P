//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : block_group.h                                  |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#include "struct_block_group.h"

#ifndef BLOCK_GROUP_H
#define BLOCK_GROUP_H

/** create a new block Groupe
 *  %return : pointer on the new Block Group 
 */
blockGroup* newBlockGroup();

/** Free a Block group 
 *  %param block_group : block group that you need to free
 */
void freeBlockGroup(blockGroup* block_group);

#endif /* BLOCK_GROUP_H included */
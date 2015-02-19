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

/* Create a new groupe with the filename as name
 * %param filename : name of the new group
 * %return : Return a pointer on the new group
 */
Group* newGroup(char* const filename);

/* Free a group
 * %param group : pointer on the group that you need to free
 */
void freeGroup(Group* group);

/* Add and create in needed a group to the blockGroup according to the filename
 * %param block_group : pointer of the block_groupe where you need to add / create a group
 * %param filename : name if the new group
 * %return : -1 if failure
 *           position of the new groupe otherwise
 */
int addGroup( blockGroup* block_group, char* const filename );

/* remove a group from a block group
 * %param block_group : block_group where you need to remove the group
 * %param pos : position of the group 
 */
void removeGroup( blockGroup* block_group, int pos );

/* Check if the group is existing in the block_group according to the filename
 * %param block_group : block_group that we need to check
 * %param filename : name of the group that we are looking for
 * %return : position of the group if found
 *           -1 otherwise
 */
int existGroup( blockGroup* block_group, char* const filename );

#endif /* GROUP_H included */
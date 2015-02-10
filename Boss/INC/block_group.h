//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : block_group.h                                  |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#include "struct_block_group.h"

#ifndef BLOCK_GROUP_H
#define BLOCK_GROUP_H

blockGroup* newBlockGroup();

void freeBlockGroup(blockGroup* block_group);

#endif /* BLOCK_GROUP_H included */
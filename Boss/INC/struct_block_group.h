//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_block_group.h                           |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_BLOCK_GROUP_H
#define STRUCT_BLOCK_GROUP_H

#include "struct_group.h"

#define MAX_GROUP 15

typedef struct blockGroup {
    int total;
    int server_socket;
    int max_socket;
    Group** groups;
} blockGroup;

#endif /* STRUCT_BLOCK_GROUP_H included */
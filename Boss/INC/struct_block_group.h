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
    int total;                  /* Total number of groups */
    int server_socket;          /* socket of the server */
    int max_socket;             /* id of the maximum socket */
    Group** groups;             /* array of Group */
} blockGroup;

#endif /* STRUCT_BLOCK_GROUP_H included */
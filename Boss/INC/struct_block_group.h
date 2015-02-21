//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_block_group.h                           |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_BLOCK_GROUP_H
#define STRUCT_BLOCK_GROUP_H

#include "struct_group.h"
#include "boolean.h"

#define MAX_GROUP 15

typedef struct blockGroup {
    bool flag;                  /* Flag which indicate if a ping is send */
    
    SOCKET server_socket;       /* socket of the server */
    int max_socket;             /* id of the maximum socket */
        
    int total;                  /* Total number of groups */
    Group** groups;             /* array of Group */
} blockGroup;

#endif /* STRUCT_BLOCK_GROUP_H included */
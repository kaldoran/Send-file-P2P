//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_group.h                                 |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_GROUP
#define STRUCT_GROUP

#include <stdio.h>

#include "boolean.h"
#include "struct_client.h"

typedef struct Group {
    char name[FILENAME_MAX];            /* name of the group */
    
    char* checker;                  /* a boolean array if checker[i] is at 1 then the client respond */
    
    int total;                      /* total number of client into the client array */
    Client* client;                 /* Array of client */
    
} Group;

#endif /* STRUCT_GROUP included */
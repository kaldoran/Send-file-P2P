//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_group.h                                 |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_GROUP
#define STRUCT_GROUP

#include <limits.h>

#include "boolean.h"
#include "struct_client.h"

typedef struct Group {
    char name[NAME_MAX];
    
    bool flag;
    char* checker;
    
    int total;
    Client* client;
    
} Group;

#endif /* STRUCT_GROUP included */
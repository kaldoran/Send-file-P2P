//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_group.h                                 |
// DATE : 10/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_GROUP
#define STRUCT_GROUP

#include <limits.h>

#include "boolean.h"
#include "struct_collector.h"

typedef struct Group {
    char name[NAME_MAX];
    
    bool flag;
    char* checker;
    
    int total;
    Collector* client;
    
} Group;

#endif /* STRUCT_GROUP included */
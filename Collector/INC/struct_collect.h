//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : struct_collect.c                               |
// DATE : 07/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_COLLECT_H
#define STRUCT_COLLECT_H

#include "socket.h"

typedef struct Collector {
    SOCKET sock;
    char* volumes; /* Finally a boolean array but in char, as char is on 1 octet */

} Collector;

#endif

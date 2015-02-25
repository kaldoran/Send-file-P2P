//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : struct_collect.c                               |
// DATE : 07/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_COLLECT_H
#define STRUCT_COLLECT_H

#include "socket.h"
#include "struct_client.h"

typedef struct Collector {
    Client c;       // Client corresponding to the Collector.
    char* volumes;  // Binary array for the Collector's volumes list (ex: if volumes[0]=1 then the Collector has the volume number 0)

} Collector;

#endif

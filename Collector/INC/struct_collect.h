//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : struct_collect.c                               |
// DATE : 07/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_COLLECT_H
#define STRUCT_COLLECT_H

typedef struct Collector {
    Socket *sock;
    int nb_volumes;
    char* volumes; /* Finally a boolean array but in char, as char is on 1 octet */

} Collector;

#endif

//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : struct_collect.c                               |
// DATE : 07/02/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_COLLECT_H
#define STRUCT_COLLECT_H

typedef struct Collector {
    int id_socket;
    int nb_volumes;
    char* volumes;
} Collector;

#endif

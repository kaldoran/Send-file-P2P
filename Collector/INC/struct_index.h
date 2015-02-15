//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_index.c                                 |
// DATE : 31/01/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_INDEX_H
#define STRUCT_INDEX_H

#include "socket.h"
#include "struct_client.h"

typedef struct Index {
    Client c;
    char file[32];    /* Name of file */
    long int file_size;
    int  pack_size;  /* Port pour la connection */
    int nb_package;
    char **sha; /* N package got N Sha1 of 40 length */
} Index;

#endif

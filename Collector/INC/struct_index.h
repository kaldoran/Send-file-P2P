//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_index.c                                 |
// DATE : 31/01/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_INDEX_H
#define STRUCT_INDEX_H

#include <netdb.h>

typedef struct Index {
    Socket sock;
    char file[32];    /* Name of file */
    long int fileSize;
    int  packSize;  /* Port pour la connection */
    int nbPackage;
    char **sha; /* N package got N Sha1 of 40 length */
} Index;

#endif

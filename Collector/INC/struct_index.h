//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_index.h                                 |
// DATE : 31/01/15                                          |
//----------------------------------------------------------

#ifndef STRUCT_INDEX_H
#define STRUCT_INDEX_H

#include "socket.h"
#include "struct_client.h"

typedef struct Index {
    Client c;           // Client correponding to the boss.
    char file[32];      // Name of file.
    long int file_size; // Size of the file.
    int  pack_size;     // Size of a volume.
    int nb_package;     // Number of volumes.
    char **sha;         // Cheksums (Sha1 of 40 characters length)
    char *local_vols;   // List of volume on the local Collector.
} Index;

#endif

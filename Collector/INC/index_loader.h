//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : index_loader.c                                 |
// DATE : 31/01/15                                          |
//----------------------------------------------------------


#ifndef INDEX_LOADER_H
#define INDEX_LOADER_H

#define TAILLE_LIGNE 512

#include "struct_index.h"

char * startWith(char *s1, char *s2);

Index *new_index();

char **new_sha(int nbPackage);

void free_index(Index *index);

bool charger_index(const char *file, Index *index);

#endif /* INDEX_LOADER_H Included */

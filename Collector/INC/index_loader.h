//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : index_loader.c                                 |
// DATE : 31/01/15                                          |
//----------------------------------------------------------


#ifndef INDEX_LOADER_H
#define INDEX_LOADER_H

#define TAILLE_LIGNE 512

#include "struct_index.h"

char* startWith(char *s1, char *s2);

Index *newIndex();

char **newSha(int nbPackage);

void freeIndex(Index *index);

bool loadIndex(const char *file, Index *index);

bool initFile(Index* index, FILE* file);

#endif /* INDEX_LOADER_H Included */

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

/** Allocates and initializes a new Index.
 * 
 *  %return: Allocated and initialized new instance of Index.
 */
Index *newIndex();

/** Allocates and initializes a list of sha1.
 * 
 *  %return: Allocated and initialized list of sha1.
 */
char **newSha(int nbPackage);

/** Frees an Index.
 * 
 *  %param index: Pointer to the Index to free.
 */
void freeIndex(Index *index);

/** Loads an Index.
 * 
 *  %param file: Name of the Index file.
 *  %param index: Pointer to the instance of Index in which file will be load.
 * 
 *  %return: FALSE if the Collector can't manage to connect to the boss,
 *           TRUE otherwise.
 */
bool loadIndex(const char *file, Index *index);

/** Checks if the file is already on the local machine and initialise the local volumes list.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param file: Pointer to the file.
 * 
 *  %return : TRUE if the file is complete and its volumes checked,
 *            FALSE otherwise.
 */
bool initFile(Index* index, FILE* file);


/** Initialises and loads an Index, connects to the boss, and launches initFile.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param index_name: Name of the file of the Index.
 *  %param file: Pointer to the file.
 * 
 *  %return : TRUE if the file is complete and its volumes checked,
 *            FALSE otherwise.
 */
bool initIndex(Index* index, char const *index_name, FILE* file);

#endif /* INDEX_LOADER_H Included */

//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : index_loader.h                                 |
// DATE : 31/01/15                                          |
//----------------------------------------------------------

#ifndef INDEX_LOADER_H
#define INDEX_LOADER_H

#define TAILLE_LINE 512

#include "struct_index.h"

/** Searches if a string has a given prefix.
 * 
 *  %param s1: Prefix to seek.
 *  %param s2: String in which search the prefix.
 *  %return: s2 minus the prefix if s1 is the prefix of s2,
 *           NULL otherwise.
 */
char* startWith(char *s1, char *s2);

/** Allocates and initializes a new Index.
 * 
 *  %return: Allocated and initialized new instance of Index.
 */
Index *newIndex();

/** Allocates and initializes a list of sha1.
 * 
 *  %param nbPackage: Number of volumes.
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
 *  %return: FALSE if the Collector can't manage to connect to the boss,
 *           TRUE otherwise.
 */
bool loadIndex(const char *file, Index *index);

/** Checks if the file is already on the local machine and initialise the local volumes list.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %return : TRUE if the file is complete and its volumes checked,
 *            FALSE otherwise.
 */
bool initFile(Index* index);

/** Initialises and loads an Index, connects to the boss, and launches initFile.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param index_name: Name of the file of the Index.
 */
void initIndex(Index* index, char const *index_name);

#endif /* INDEX_LOADER_H Included */

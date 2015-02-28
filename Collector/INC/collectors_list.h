//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors_list.h                              |
// DATE : 26/02/15                                          |
//----------------------------------------------------------


#ifndef COLLECTORSLIST_H
#define COLLECTORSLIST_H

#include "struct_index.h"
#include "struct_collect.h"

/** Allocates a list of Collectors
 * 
 *  %param nb_coll: Number of Collectors in the list.
 * 
 *  %return: Allocated instance of a list of Collector.
 */
Collector** newCollectorsList(int nb_coll);

/** Fills the list of Collectors from the ip adresses given by the boss.
 *  
 *  %param collectors_list: The Collector list to fill.
 *  %param index: Pointer to the loaded Index.
 *  %param port : Port were we want to start server and also send to boss
 * 
 *  %return : number of collectors given by the boss.
 */
Collector** fillCollectorsList(int* nb_seed, Index* index, int port);

/** Finds a Collector and a volume to ask.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param coll_list: List of the Collectors given by the boss.
 *  %param nb_seed: number of Collectors in the list.
 * 
 *  %return: 2 int:
 *      -the number of first Collectors in the list who has a volume that the local Collector doesn't have.
 *      -the number of this volume.
 */
int* findCollVol(Index* index, Collector** coll_list, int nb_seed);

#endif

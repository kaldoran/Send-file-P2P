//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors_list.h                              |
// DATE : 26/02/15                                          |
//----------------------------------------------------------


#ifndef COLLECTORSLIST_H
#define COLLECTORSLIST_H

#include "struct_index.h"
#include "struct_server.h"
#include "struct_collect.h"

/** Allocates a list of Collectors
 * 
 *  %param nb_coll: Number of Collectors in the list.
 * 
 *  %return: Allocated instance of a list of Collector.
 */
Collector** newCollectorsList(int nb_coll);

/** Free a liste of collector
 *  %param coll : list to free
 *  %param nb_seed : total of collector in the list
 */
void freeCollectorsList(Collector** coll, int nb_seed);

/** Fills the list of Collectors from the ip adresses given by the boss.
 *  
 *  %param collectors_list: The Collector list to fill.
 *  %param index: Pointer to the loaded Index.
 * 
 *  %return : number of collectors given by the boss.
 */
Collector** fillCollectorsList(Server* s, Index* index);

#endif

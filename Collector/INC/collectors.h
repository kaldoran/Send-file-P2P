//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.h                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------


#ifndef COLLECTORS_H
#define COLLECTORS_H

#include "struct_index.h"
#include "struct_collect.h"

#define COLLECT_PORT 47777
#define LIST_COLL_SIZE_MAX 10

Collector* newCollect(int nb_vol);

void freeCollect(Collector *coll);

Collector** collectorsFromIps(int nb_coll, char** ips);

void askVolList(Collector* collect, int nb_vol);

int fillCollectorsList(Collector** collectors_list, Index* index);

int* findCollVol(Index* index, Collector** coll_list, int nb_seed);

#endif

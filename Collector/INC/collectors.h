//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.h                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------


#ifndef COLLECTORS_H
#define COLLECTORS_H

#include "struct_collect.h"

#define COLLECT_PORT 47777

Collector* new_collect(int nb_vol);

void free_collect(Collector *coll);

Collector** CollectorsFromIps(int nb_coll, char** ips);

void ask_vol_list(Collector* collect);

#endif

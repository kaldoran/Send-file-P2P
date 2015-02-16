//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.h                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#ifndef VOLUME_H
#define VOLUME_H

#include <stdio.h>

#include "socket.h"
#include "struct_index.h"
#include "struct_collect.h"

void getVolume(Index* index, Collector** collectors_list, int nb_seed, FILE* file);

void sendVolume(Client c, int volNum, int vol_size, FILE* file);

#endif /* VOLUME_H included */

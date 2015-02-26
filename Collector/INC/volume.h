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


/** Gets a volume.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param collectors_list: List of the collectors given by the boss.
 *  %param nb_seed: Number of Collectors in the list.
 *  %param file: Pointer to the file.
 */
void getVolume(Index* index, Collector** collectors_list, int nb_seed, FILE* file);


/** Sends a volume.
 * 
 *  %param c: Client who asks the volume.
 *  %param vol_num: Id of the volume.
 *  %param vol_size: Size of the volume.
 *  %param file: Pointer to the file.
 */
void sendVolume(Client c, int vol_num, int vol_size, FILE* file);


void sendListVolumes(Client c, Index* index);

#endif /* VOLUME_H included */

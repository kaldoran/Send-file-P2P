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
#include "struct_server.h"
#include "struct_collect.h"

/** Sends a volume.
 * 
 *  %param c: Client who asks the volume.
 *  %param vol_num: Id of the volume.
 *  %param vol_size: Size of the volume.
 *  %param file: Pointer to the file.
 */
void sendVolume(Client c, int vol_num, int vol_size, FILE* file);

/** Gets a volume.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param collectors_list: List of the collectors given by the boss.
 *  %param s: The instance of the local Server.
 *  %return : TRUE if the file is complet,
 *            FALSE otherwise.
 */
bool getVolume(Index* index, Collector** collectors_list, Server* s);

/** Finds a volume to ask.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param coll: Pointer of the Collector at which we search a volume.
 *  %return: Id of a volume available at a Collector and that the local Collector doesn't have,
 *           -1 if there is no such volume.
 */
int findCollVol(Index* index, Collector* coll);

/** Asks the liste of volume that a collector has.
 * 
 *  %param collect: Collector whose to ask the volumes.
 *  %param nb_vol: Number of volume composing the file.
 */
void askVolList(Collector* collect, int nb_vol);

/** Sends the local list of volumes.
 * 
 *  %param c: Client who asks the list.
 *  %param index: Pointer to the loaded Index.
 *  
 *  Send FULL_VOLUME_MSG if we've got all volume
 *  Send NONE_VOLUME_MSG if we've got no volume
 *  Send index->local_vols if we've got a part of volume
 */
void sendListVolumes(Client c, Index* index);

#endif /* VOLUME_H included */

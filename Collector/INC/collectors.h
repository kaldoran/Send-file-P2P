//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.h                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#ifndef COLLECTORS_H
#define COLLECTORS_H

#include "struct_index.h"
#include "struct_server.h"
#include "struct_collect.h"

#define COLLECT_PORT 47777
#define LIST_COLL_SIZE_MAX 10

/** Allocates a new collector.
 * 
 *  %param nb_vol: Number of volume composing the file.
 *  %return : Pointer to the new Collector allocated.
 */
Collector* newCollect(int nb_vol);

/** Frees an instance of Collector.
 * 
 *  %param coll: Pointer to the Collector to free.
 */
void freeCollect(Collector *coll);

/** Asks the liste of volume that a collector has.
 * 
 *  %param collect: Collector whose to ask the volumes.
 *  %param nb_vol: Number of volume composing the file.
 */
void askVolList(Collector* collect, int nb_vol);

/** The execution loop of the Collector.
 * 
 * %param index_name: Path of the Index to load.
 * %param port : port on which you want to start the collector
 */
void startCollector(char *index_name, const int port);

/** Initialazes the Collector's execution loop
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param s: The instance of the local Server.
 *  %param rdfs: Parameter used for the one-threaded gestion of the Collector's features.
 */
void initFd(Index* index, Server* s, fd_set* rdfs);

/** Sends the volumes that the connected clients ask, or removes the clients of the connected Client list if they are no more connected.
 * 
 *  %param s: The instance of the local Server.
 *  %param index: Pointer to the loaded Index.
 *  %param rdfs: Parameter used for the one-threaded gestion of the Collector's features.
 */
void manageClient(Server* s, Index *index, fd_set* rdfs);

/** Receive from the boss a name of file and respond "Exist" if the file is available on the local machine, "NotExist" otherwise.
 * 
 *  %param index: Pointer to the loaded Index.
 */
void pong(Index *index);

/** Send the file name and the port to the server 
 *  
 *  %param index : index which contains the socket to boss
 *  %param port : which port we need to send 
 */
void sendFileName(Index *index, int port);

#endif

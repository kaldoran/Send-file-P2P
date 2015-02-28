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

/** Allocates a new collector.
 * 
 *  %param nb_vol: Number of volume composing the file.
 * 
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

/** Creates a Client un fonction of a given ip adress.
 * 
 *  %param client: Instance of Client in which create the client.
 *  %param ip: Ip adress of the client.
 * 
 *  %return : Instance of Client corresponding to the IP adress.
 */
void createClientFromIp(Client* client, char* ip);

/** The execution loop of the Collector.
 * 
 * %param index_name: Path of the Index to load.
 */
void startCollector(char const *index_name);

/** Initialazes the Collector's execution loop
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param client: List of Client connected to the local Collector.
 *  %param nb_leach: Number of Client connected to the local Collector.
 *  %param rdfs: Parameter used for the one-threaded gestion of the Collector's features.
 */
void initFd(Index* index, Client* client, int nb_leach, fd_set* rdfs);

/** Adds a new Client in the list of connected clients if the limit of connexions is not reached.
 * 
 *  %param client_tab: List of Client connected to the local Collector.
 *  %param seed_socket: Id of the local Collector's socket.
 *  %param max_socket: Pointer to the id of the last connected client.
 *  %param nb_leach: Number of Client connected to the local Collector.
 * 
 *  %return 1 if a Client is added, 0 otherwise.
 */
int addNewClient(Client* client_tab, int seed_socket, int* max_socket, int nb_leach);

/** Sends the volumes that the connected clients ask, or removes the clients of the connected Client list if they are no more connected.
 * 
 *  %param client_tab: List of Client connected to the local Collector.
 *  %param nb_leach: Pointer to the number of Client connected to the local Collector.
 *  %param max_socket: Pointer to the id of the last connected client.
 *  %param index: Pointer to the loaded Index.
 *  %param file: Pointer to the shared file.
 *  %param rdfs: Parameter used for the one-threaded gestion of the Collector's features.
 */
void manageClient(Client *client_tab, int *nb_leach, int *max_socket, Index *index, FILE *file, fd_set* rdfs);

/** Receive from the boss a name of file and respond "Exist" if the file is available on the local machine, "NotExist" otherwise.
 * 
 *  %param index: Pointer to the loaded Index.
 */
void pong(Index *index);

#endif

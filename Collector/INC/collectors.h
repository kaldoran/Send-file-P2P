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

void startCollector(char const *index_name);

void initFd(Index* index, Client* client, int nb_leach, fd_set* rdfs);

int addNewClient(Client* client_tab, int seed_socket, int* max_socket, int nb_leach);

void manageClient(Client *client_tab, int *nb_leach, int *max_socket, Index *index, FILE *file, fd_set* rdfs);

#endif

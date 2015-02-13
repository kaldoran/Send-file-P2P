//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : collector.h                                    |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "boolean.h"
#include "struct_collector.h"

Collector *newClient(int const number);

void closeClient(Collector *client,int const total);

void freeClient(Collector *client);

Collector acceptClient( int const server_socket );

void sendClient(Collector *client, int number, int total, int to);

bool addClient(Collector *client, Collector new, int *total);

void removeClient(Collector *client, int const pos,  int *total, int *max_socket);

#endif /* COLLECTOR_H included */
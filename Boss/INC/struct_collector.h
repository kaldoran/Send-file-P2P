//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : struct_client.c                                |
// DATE : 08/02/15                                          |
//----------------------------------------------------------
#ifndef STRUCT_COLLECTOR_H
#define STRUCT_COLLECTOR_H

#define MAX_CONNEXION 15

typedef struct Collector {
    int id_socket; 
    char ip[15];
} Collector;

#endif /* STRUCT_COLLECTOR_H included */

//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : tcp.h                                          |
// DATE : 01/02/15                                          |
//----------------------------------------------------------

#ifndef TCP_H
#define TCP_H

#define SEND 0
#define RECEIVED 1

#if DEBUG
    #define AFFICHE(DATA) printf("Recu : %s.\n", (char *)DATA);
#else 
    #define AFFICHE(DATA) ;
#endif

#include "boolean.h"
#include "struct_socket.h"


Socket* new_socket();

void free_socket(Socket *s);

bool tcp_start(Socket *s);

int tcp_action(Socket *s, void *data, int data_length, int type);

#endif /* TCP_H included */
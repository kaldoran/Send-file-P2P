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

#include "socket.h"
#include "boolean.h"
#include "struct_client.h"

/** Connects to a Client.
 * 
 *  %param c: Client to connect to.
 * 
 *  %return: TRUE if the connection succeded,
 *           FALSE otherwise.
 */
bool tcpStart(Client c);

/** Sends/Receives data to/from a Client.
 * 
 *  %param c: Client considered.
 *  %param data: Data to send or to receive.
 *  %param data_length: Number of bits in the data.
 *  %param type: SEND to send data, RECEIVED to receive data.
 * 
 *  %return: the number of bit sended or received,
 *           -1 if incorrect type.
 */
int tcpAction(Client c, void *data, int data_length, int type);

#endif /* TCP_H included */

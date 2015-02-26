//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.h                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H

#include "boolean.h"
#include "struct_client.h"

/** Allocate pointeur for an array of client.
 * 
 *  %param number : number of client.
 * 
 *  %retun : pointeur on an array of client.
 */
Client *newClientArray(int const number);

/** Close an array of client.
 * 
 *  %param client : the array of client.
 *  %param total : total number of client.
 */
void closeClientArray(Client *client,int const total);

/** Free an array of client.
 * 
 *  %param client : array that you want to free.
 */
void freeClientArray(Client *client);

/** init a Client
 * 
 *  %return : a client which one had been initialized.
 */
Client initClient();

/** Accept a client from the 'server_socket' socket.
 * 
 *  %param server_socket : socket of the server, which on you want to accept a client.
 * 
 *  %return : the information about the client.
 */
Client acceptClient( int const server_socket );

/** Add a client to an array of client.
 * 
 *  %param client : array where you need to add the new client.
 *  %param new : the new client that you need to add.
 *  %param total : pointeur on the total number of client.
 * 
 *  %return : True if we succeed into adding a client.
 *            False otherwise.
 */
bool addClient(Client *client, Client new, int *total);

/** Remove a client frop the array of client.
 * 
 *  %param groupe : pointer on the group where you need to remove a client.
 *  %param pos : position of the client in the array.
 *  %param max_socket : max id of the socket.
 * 
 *  %return : return the new max_socket value.
 */
void removeClient(Client *client, int const pos,  int *total, int *max_socket);

#endif /* CLIENT_H included */

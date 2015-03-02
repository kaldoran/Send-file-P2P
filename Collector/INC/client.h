//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.h                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H

#include "boolean.h"
#include "struct_server.h"
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


/** Adds a new Client in the list of connected clients if the limit of connexions is not reached.
 * 
 *  %param s: The instance of the local Server.
 * 
 *  %return 1 if a Client is added, 0 otherwise.
 */
int addClient(Server* s);

/** Remove a client frop the array of client.
 * 
 *  %param s: The instance of the local Server.
 *  %param pos : position of the client in the array.
 */
void removeClient(Server* s, int const pos);

#endif /* CLIENT_H included */

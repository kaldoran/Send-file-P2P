//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : client.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef CLIENT_H
#define CLIENT_H

#include "boolean.h"
#include "group.h"
#include "struct_client.h"
#include "struct_block_group.h"

#define MAX_COLLECTOR_SEND 10

/** Allocate pointeur for an array of client 
 *  %param number : number of client
 *  %retun : pointeur on an array of client
 */
Client *newClientArray(int const number);

/** Close an array of client 
 *  %param client : the array of client
 *  %param total : total number of client 
 */
void closeClientArray(Client *client,int const total);

/** Free an array of client
 *  %param client : array that you want to free
 */
void freeClientArray(Client *client);

/** init a Client
 *  %return : a client which one had been initialized 
 */
Client initClient();

/** Accept a client from the 'server_socket' socket
 *  %param server_socket : socket of the server, which on you want to accept a client
 *  %return : the information about the client
 */
Client acceptClient( int const server_socket );

/** Handle new connexion of a client
 *  %param block_group : Block group on which there is the socket server and the array of client
 */
void handleNewClient(blockGroup* block_group);

/** Handle client, Check message and handle them
 *  %param block_group : Block groupe to handle
 *  %param rdfs : fd set where the descriptor of socket is
 */
void handlerClient(blockGroup* block_group, fd_set* rdfs);

/** Send all client to a socket 
 *  %param client : array of client which you wnat to send
 *  %param total : total number of client
 *  %param to : position of the client into the client array 
 */ 
void sendClient(Client *client, int total, int to);

/** Add a client to an array of client
 *  %param client : array where you need to add the new client
 *  %param new : the new client that you need to add
 *  %param total : pointeur on the total number of client
 *  %return : True if we succeed into adding a client
 *            False otherwise
 */
bool addClient(Client *client, Client new, int *total);

/** Remove a client frop the array of client
 *  %param groupe : Block group where you need to remove a client
 *  %param client_pos : position of the client in the array group array
 *  %param group_pos : position of the group in the block_group
 */
void removeClient( blockGroup* block_group, int const client_pos, int const group_pos);

#endif /* CLIENT_H included */

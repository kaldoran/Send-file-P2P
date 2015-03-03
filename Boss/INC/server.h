//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "struct_client.h"
#include "struct_block_group.h"

#define PORT 42000 /* Listing port for server */

/** init a socket for a server
 *  %return : the initialized socket for the server
 */ 
int initServer();

/** Start the server
 *  Infinit loop that stop on user input 
 */
void startServer();

/** Create the handler on all socket and STDIN
 *  %param block_group : block group which contains all socket whre you need to set the fd_set
 *  %param rdfs : pointer on the fd_set to complexe
 */
void setHandler(blockGroup *block_group, fd_set *rdfs);

/** close a server
 *  %param server_socket : socket of the server that you need to close
 */
void closeServer(blockGroup *block_group);

#endif /* SERVER_H included */
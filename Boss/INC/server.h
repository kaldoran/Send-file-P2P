//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "struct_client.h"
#include "struct_block_group.h"


/** init a socket for a server
 *  %return : the initialized socket for the server
 */ 
int initServer();

void startServer();

void setHandler(blockGroup *block_group, fd_set *rdfs);

/** close a server
 *  %param server_socket : socket of the server that you need to close
 */
void closeServer(blockGroup *block_group);

#endif /* SERVER_H included */
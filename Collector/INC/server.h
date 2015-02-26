//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "struct_client.h"

/** init a socket for a server
 * 
 *  %return : the initialized socket for the server
 */ 
int initServer();

/** close a server
 * 
 *  %param server_socket : socket of the server that you need to close
 */
void closeServer(int server_socket);

#endif /* SERVER_H included */

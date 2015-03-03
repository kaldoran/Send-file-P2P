//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : server.h                                       |
// DATE : 09/02/15                                          |
//----------------------------------------------------------

#ifndef SERVER_H
#define SERVER_H

#include "struct_server.h"

/** Create a new server and allocate it/ initialize it according to a port
 *  %param port : port of the new server
 */
Server* newServer(const int port);

/** free the server Structure
 *  %param s : Structure which them we want to free
 */
void freeServer(Server *s);

/** init a socket for a server
 * 
 *  %return : the initialized socket for the server
 */ 
int initServer(const int port);

/** close a server
 * 
 *  %param server_socket : socket of the server that you need to close
 */
void closeServer(int server_socket);

#endif /* SERVER_H included */


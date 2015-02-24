//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : ping.h                                         |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#ifndef PING_H
#define PING_H

#include "struct_block_group.h"
 
/* Time in seconde before check respond */
#define PONG_CHECKER_TIMER 1
/* Time in second between 2 presence check */
#define PING_TIMER 300

/** handle if we need to ask presence or check the respond
 *  %param block_group : block gorup where you need to handle presence
 *  %return ! number of second to wait
 */
int handlerPresence(blockGroup *block_group);

/** Send a message to all client to check there presence
 *  %param group : group where you need to ask presence 
 */
void askPresence(Group *group);

/** Check if all client had respond
 *  %param group : group to check
 *  %param max_socket : pointeur on the max_socket number
 */ 
void checkPresence(Group *group, int *max_socket);

#endif /* PING_H included */

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

int handlerPresence(blockGroup *block_group);

void askPresence(Group *group);

void checkPresence(Group *group, int *max_socket);

#endif /* PING_H included */
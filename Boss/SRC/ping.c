//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : ping.c                                         |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#include "client.h"
#include "ping.h"

int handlerPresence(blockGroup *block_group) {
    int i;
    
    for(i = 0; i < block_group->total; i++) {
        
        if ( block_group->flag == TRUE ) {
            askPresence(block_group->groups[i]);
        } else {
            checkPresence(block_group->groups[i], &block_group->max_socket);
        }
    }
    
    block_group->flag = !block_group->flag;
    
    return (block_group->flag == TRUE) ? PONG_CHECKER_TIMER : PING_TIMER;
}

void askPresence(Group *group) {
    int i;

    for ( i = 0; i < group->total; i++ ) {
        /* Send the same message to all client from a groups */
        send(group->client[i].id_socket, group->name, sizeof(*group->name), 0);
    }   
    return;  
}

void checkPresence(Group *group, int *max_socket) {
    int i;
    
    for ( i = 0; i < group->total; i++ ) {
        /* if the ckerckers flag if at 0 then i didn't respond in time */
        if ( group->checker[i] == 0 ) {
            *max_socket = removeClient(group, i, *max_socket );
        }
    }

    return;
}
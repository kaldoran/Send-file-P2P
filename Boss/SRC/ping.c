//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : ping.c                                         |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#include <string.h>

#include "client.h"
#include "ping.h"

int handlerPresence(blockGroup *block_group) {
    int i;

    for(i = 0; i < block_group->total; i++) {   
        if ( block_group->flag == FALSE ) {
            memset(block_group->groups[i]->checker, '0', block_group->groups[i]->total);
            askPresence(block_group->groups[i]);
        } else {
            checkPresence(block_group, i);
            
            if ( block_group->groups[i]->total == 0 ) { removeGroup( block_group, i );  --i; } /* If needed remove the group */
        }
    }
    
    block_group->flag = !block_group->flag;
    
    return (block_group->flag == TRUE) ? PONG_CHECKER_TIMER : PING_TIMER;
}

void askPresence(Group *group) {
    int i;
    printf("\n[PING] Let send the ping test !\n");
    for ( i = 0; i < group->total; i++ ) {
        /* Send the same message to all client from a groups */
        send(group->client[i].id_socket, group->name, sizeof(group->name), 0);
    }   
    return;  
}

void checkPresence(blockGroup *block_group, int const group_pos ) {
    int i;
    Group* group = block_group->groups[group_pos];
    printf("[PONG] Let check the pong result \n");
    for ( i = 0; i < group->total; i++ ) {
        /* if the ckerckers flag if at 0 then i didn't respond in time */
        if ( group->checker[i] == '0' ) {
            printf("[INFO] Client %d do not respond to ping in time.\n", group->client[i].id_socket);
            removeClient(block_group, i, group_pos );
            --i; /* We remove one client, so we apply -1 to i too */
        }
    }

    return;
}

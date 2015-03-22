//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "tcp.h"
#include "error.h"
#include "inout.h"
#include "socket.h"
#include "volume.h"
#include "client.h"
#include "server.h"
#include "boolean.h"
#include "windows.h"
#include "message.h"
#include "collectors.h"
#include "index_loader.h"
#include "verification.h"
#include "collectors_list.h"

Collector* newCollect(int nb_vol) {
    Collector* collect;
    
    if ( (collect = calloc(1, sizeof(*collect))) == NULL) {
        QUIT_MSG("Can't Allocate Collector : ");
    }
        
    if ((collect->volumes = calloc(nb_vol, sizeof(char))) == NULL) {
        QUIT_MSG("Can't Allocate Collector's volume list : ");
    }
        
    return collect;
}

void freeCollect(Collector *coll) {
    closesocket((coll->c).id_socket);
    
    if ( coll->volumes != NULL ) {
        free(coll->volumes);
    }
    
    free(coll);
}

void startCollector(char *index_name, const int port, char* sharing_rep){
    int timer;
    fd_set rdfs;
    Index *index = NULL;
    Collector** collectors_list = NULL;
    struct timeval tval;

    Server *s = newServer(port);
    
    tval.tv_sec  = S_NEW_LIST;
    tval.tv_usec = 0; 
    
    printf("\n[IMPORTANT] : Press Enter to Stop the Collector\n\n");  
        
    index = newIndex();
    
    initIndex(index, index_name);
    
    mkdirRec(sharing_rep);
        
    s->full_file = initFile(index);
    
    /* Check if we need to update max socket */
    if ( s->max_socket < index->c.id_socket ) { 
        s->max_socket = index->c.id_socket; 
    }

    s->file = fopen(index->file, "r+");
    
    sendFileName(index, port); 
    
    if(!s->full_file) {
        collectors_list = fillCollectorsList(s, index);
    }
    
    for ( ;; ) {
        initFd(index, s, &rdfs);
        
        if(!s->full_file && s->nb_seed != 0) {          
            s->full_file = getVolume(index, collectors_list, s);
        }        

        if( (timer = select(s->max_socket + 1, &rdfs, NULL, NULL, &tval)) == -1) {
            QUIT_MSG("Can't select : ");
        }

        if ( timer == 0 ) {
            if ( !s->full_file && s->nb_seed == 0) {
                /* If we are here, then the pointer, had not been allocated */
                collectors_list = fillCollectorsList(s, index);
                tval.tv_sec  = S_NEW_LIST;
            }
        }

        #ifdef linux
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;
        }
        else
        #endif
        if( FD_ISSET(index->c.id_socket, &rdfs) ) {
            pong(index);
        }
        else if( FD_ISSET(s->seed_socket, &rdfs) ) {
            s->nb_leach += addClient(s);
        }
        else {
            manageClient(s, index, &rdfs);
        }
    }

    printf("[BYE] Collector stop.\n");

    close(index->c.id_socket);
    freeIndex(index);
    freeServer(s);

    return;
}

void initFd(Index* index, Server* s, fd_set* rdfs){
    int i;

    FD_ZERO(rdfs);

    #ifdef linux
    FD_SET(STDIN_FILENO, rdfs);
    #endif
    FD_SET(index->c.id_socket, rdfs);
    FD_SET(s->seed_socket, rdfs);

    for(i = 0; i < s->nb_leach; i++) {
        FD_SET(s->client[i].id_socket, rdfs);
    }
}

void manageClient(Server* s, Index *index, fd_set* rdfs){
    char in_buf[COLLECTOR_READER_SIZE];
    char *token;
    int i;
    int tmpVal;

    for(i = 0; i < s->nb_leach; i++) {
        if ( FD_ISSET(s->client[i].id_socket, rdfs) ) {
            memset(in_buf, '\0', COLLECTOR_READER_SIZE);

            tmpVal = tcpAction(s->client[i], in_buf, COLLECTOR_READER_SIZE, RECEIVED);
            removeEndCarac(in_buf);
            
            if ( tmpVal <= 0 ) {
                removeClient(s, i);
                --i; /* When we remove a client we need to apply this to i */
            } else {
                printf("\n[INFO] (%d) message recu '%s' [Client : %d].\n", tmpVal, in_buf, s->client[i].id_socket);
                removeEndCarac(in_buf);

                if ( (token = startWith(PREFIX_OF_VOLUME_MSG, in_buf)) != NULL ) {
                    sendVolume(s->client[i], atoi(token), index->pack_size, s->file);
                }
                else if( strcmp(in_buf, LIST_OF_VOLUMES_MSG) == 0 ) {
                    sendListVolumes(s->client[i], index);
                }
            }
        }
    }
}

void pong(Index *index){
    char in_buf[FILENAME_MAX] = "";
        
    if ( tcpAction(index->c, in_buf, FILENAME_MAX, RECEIVED) <= 0 ) {
        #ifdef linux
			errno = ECONNRESET;
		#endif
        QUIT_MSG("Boss disconnect us : ");
    }
    removeEndCarac(in_buf);
    DEBUG_MSG("Received : %s", in_buf); 
    printf("[INFO] Received ping from Boss.\n");
    
    if(strcmp(in_buf, index->file) == 0 && fileExist(in_buf)){
        tcpAction(index->c, FILE_EXIST_MSG, sizeof(FILE_EXIST_MSG), SEND);
    }
    else {
        tcpAction(index->c, FILE_NOT_EXIST_MSG, sizeof(FILE_NOT_EXIST_MSG), SEND);
    }
    
    return;
}

void sendFileName(Index *index, int port) {
    char out_buf[sizeof(index->file) + 6] = "";
    
    sprintf(out_buf, "%s|%d", index->file, port);

    tcpAction(index->c, out_buf, sizeof(out_buf), SEND);
    
    return;
}

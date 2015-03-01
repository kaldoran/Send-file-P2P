//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tcp.h"
#include "error.h"
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
#include "struct_index.h"
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
    if ( coll->volumes != NULL ) {
        free(coll->volumes);
    }
    free(coll);
}

void askVolList(Collector* collect, int nb_vol) {
    char data[nb_vol];
    tcpAction(collect->c, LIST_OF_VOLUMES_MSG, sizeof(LIST_OF_VOLUMES_MSG), SEND);
    
    tcpAction(collect->c, data, nb_vol, RECEIVED);
    removeEndCarac(data);
    
    switch(*data){
        case 'f': memset(collect->volumes, '1', nb_vol);
                  break;
        case 'n': memset(collect->volumes, '0', nb_vol);
                  break;
        default: strcpy(collect->volumes, data);
    }
}

void createClientFromIp(Client* client, char* ip){
    struct hostent *h;
    
    *client = initClient();

    if( (h = gethostbyname(ip)) != NULL ) {
        memcpy(&client->sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
    }
    
    client->sock_info.sin_port = htons(COLLECT_PORT);
}

void startCollector(char *index_name, const int port){
    int timer;
    fd_set rdfs;
    Index *index = NULL;
    Collector** collectors_list = NULL;
    struct timeval tval;

    Server *s = newServer(port);
    
    tval.tv_sec  = 60;
    tval.tv_usec = 0; 
    
    index = newIndex();
    
    initIndex(index, index_name);
    s->full_file = initFile(index);
    
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
            if ( s->nb_seed == 0 ) {
                /* If we are here, then the pointer, had not been allocated */
                collectors_list = fillCollectorsList(s, index);
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
            s->nb_leach = s->nb_leach + addNewClient(s);
        }
        
        manageClient(s, index, &rdfs);
    }
    

    freeIndex(index);
    free(index_name);
    
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
    
    for(i = 0; i < s->nb_leach; i++) {
        FD_SET(s->client[i].id_socket, rdfs);
    }
}

int addNewClient(Server* s){
    Client tmp = acceptClient(s->seed_socket);
            
    if(s->nb_leach < MAX_CONNEXION) {
        if ( s->max_socket < tmp.id_socket ) {
            DEBUG_MSG("Change the max socket.");
            s->max_socket = tmp.id_socket;
        }

        s->client[s->nb_leach] = tmp;
        
        return 1;
    }
    
    printf("Max number of client reached");
    close(tmp.id_socket);
    
    return 0;
}

void manageClient(Server* s, Index *index, fd_set* rdfs){
    char in_buf[25];
    char *token;
    int i;
    
    for(i = 0; i < s->nb_leach; i++) {
        if ( FD_ISSET(s->client[i].id_socket, rdfs) ) {
            memset(in_buf, '\0', 25);

            printf("Client ask for something\n");

            if ( tcpAction(s->client[i], in_buf, 25, RECEIVED) == 0 ) {
                printf("Client disconnect\n");
                removeClient(s, i);
            } else {
                removeEndCarac(in_buf);
                
                if ( (token = startWith(in_buf, PREFIX_OF_VOLUME_MSG)) != NULL ) {
                    sendVolume(s->client[i], atoi(token), index->pack_size, s->file);
                }
                else if( strcmp(in_buf, LIST_OF_VOLUMES_MSG) == 0 ) {
                    sendListVolumes(s->client[i], index);
                }
                else {
                    printf("Oh Mama he send something stupid '%s'", in_buf);
                }
            }
        }
    }
}

void pong(Index *index){
        char in_buf[FILENAME_MAX];
    
        memset(in_buf, '\0', FILENAME_MAX);
            
        tcpAction(index->c, in_buf, FILENAME_MAX, RECEIVED);
        removeEndCarac(in_buf);
    
        if(strcmp(in_buf, index->file) == 0 && fileExist(in_buf)){
            tcpAction(index->c, FILE_EXIST_MSG, sizeof(FILE_EXIST_MSG), SEND);
        }
        else{
            tcpAction(index->c, FILE_NOT_EXIST_MSG, sizeof(FILE_NOT_EXIST_MSG), SEND);
        }
}

void sendFileName(Index *index, int port) {
    char out_buf[sizeof(index->file) + 6] = "";
    sprintf(out_buf, "%s|%d", index->file, port);

    tcpAction(index->c, out_buf, sizeof(out_buf), SEND);
    
    return;
}

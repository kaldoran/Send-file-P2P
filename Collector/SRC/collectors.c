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

    /* Server *s = newServer(port); */
    /* Remplacera */
    int nb_seed = 0, nb_leach = 0;
    bool full_file = FALSE;
    Client *client = newClientArray(MAX_CONNEXION);
    FILE *file = NULL;
    SOCKET seed_socket = initServer(port);
    int max_socket = seed_socket;
    /*** Tout ceci ci dessus */
    
    tval.tv_sec  = 60;
    tval.tv_usec = 0; 
    
    index = newIndex();
    
    initIndex(index, index_name);
    full_file = initFile(index);
    
    file = fopen(index->file, "r+");
    
    if(!full_file) {
        collectors_list = fillCollectorsList(&nb_seed, index);
    }
    
    for ( ;; ) {
        initFd(index, client, nb_leach, &rdfs); /* Ici on pourra changer pour passer le pointeur de serveur */
        
        if(!full_file && nb_seed != 0) {          
            full_file = getVolume(index, collectors_list, nb_seed, file); /* La meme ici */
        }
        
        if( (timer = select(max_socket + 1, &rdfs, NULL, NULL, &tval)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if ( timer == 0 ) {
            if ( nb_seed == 0 ) {
                /* If we are here, then the pointer, had not been allocated */
                collectors_list = fillCollectorsList(&nb_seed, index);
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
        else if( FD_ISSET(seed_socket, &rdfs) ) {
            /* Ici aussi */
            nb_leach += addNewClient(client, seed_socket, &max_socket, nb_leach);
        }
        
        /* Ici aussi */
        manageClient(client, &nb_leach, & max_socket, index, file, &rdfs);
    }
    

    freeIndex(index);
    free(index_name);
    
    /* freeServer(s); */
    /* Deviendra donc useless */
    freeClientArray(client);
    fclose(file);
    /* ****** */
    
    return;
}

void initFd(Index* index, Client* client, int nb_leach, fd_set* rdfs){
    int i;
    
    FD_ZERO(rdfs);
    
    #ifdef linux
    FD_SET(STDIN_FILENO, rdfs);
    #endif
    FD_SET(index->c.id_socket, rdfs);
    
    for(i = 0; i < nb_leach; i++) {
        FD_SET(client[i].id_socket, rdfs);
    }
}

int addNewClient(Client* client_tab, int seed_socket, int* max_socket, int nb_leach){
    Client tmp = acceptClient(seed_socket);
            
    if(nb_leach < MAX_CONNEXION) {
        if ( *max_socket < tmp.id_socket ) {
            DEBUG_MSG("Change the max socket\n");
            *max_socket = tmp.id_socket;
        }

        client_tab[nb_leach] = tmp;
        
        return 1;
    }
    
    printf("Max number of client reached");
    close(tmp.id_socket);
    
    return 0;
}

void manageClient(Client *client_tab, int *nb_leach, int *max_socket, Index *index, FILE *file, fd_set* rdfs){
    char in_buf[25];
    char *token;
    int i;
    
    for(i = 0; i < *nb_leach; i++) {
        if ( FD_ISSET(client_tab[i].id_socket, rdfs) ) {
            memset(in_buf, '\0', 25);

            printf("Client ask for something\n");

            if ( tcpAction(client_tab[i], in_buf, 25, RECEIVED) == 0 ) {
                printf("Client disconnect\n");
                removeClient(client_tab, i, nb_leach, max_socket );
            } else {
                removeEndCarac(in_buf);
                
                if ( (token = startWith(in_buf, PREFIX_OF_VOLUME_MSG)) != NULL ) {
                    sendVolume(client_tab[i], atoi(token), index->pack_size, file);
                }
                else if( strcmp(in_buf, LIST_OF_VOLUMES_MSG) == 0 ) {
                    sendListVolumes(client_tab[i], index);
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

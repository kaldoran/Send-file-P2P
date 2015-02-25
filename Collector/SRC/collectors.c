//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For fork and kill

#include "tcp.h"
#include "error.h"
#include "socket.h"
#include "volume.h"
#include "client.h"
#include "server.h"
#include "boolean.h"
#include "windows.h"
#include "collectors.h"
#include "index_loader.h"
#include "verification.h"
#include "struct_index.h"


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
    tcpAction(collect->c, "ListOfVolumes", 13, SEND);
    
    tcpAction(collect->c, data, nb_vol, RECEIVED);
    
    switch(*data){
        case 'f': memset(collect->volumes, '1', nb_vol);
                  break;
        case 'n': memset(collect->volumes, '0', nb_vol);
                  break;
        default: strcpy(collect->volumes, data);
    }
}

int fillCollectorsList(Collector** collectors_list, Index* index){
    int nb_seed = 0;
    char in_buf[25];
    char *token;
    //struct hostent *h;
    
    tcpAction(index->c, index->file, sizeof(index->file), SEND);
        
    tcpAction(index->c, "ListOfCollectors", 16, SEND);
        
    do {
        memset(in_buf, '\0', 25);
            
        tcpAction(index->c, in_buf, 25, RECEIVED);
        printf("Received : %s\n",  in_buf);
            
        token = strtok(in_buf, "|");
        printf("Num of collector : %d\n", atoi(token));
        
        token = strtok(NULL, "|");
           printf("Ip of Collector : %s\n", token);
        
        collectors_list[nb_seed] = newCollect(index->nb_package);

        createClientFromIp(&collectors_list[nb_seed]->c, token);
        
        if(tcpStart(collectors_list[nb_seed]->c) == FALSE){
            printf("Can't connect to collector n°%d", nb_seed);
        }
        else{
            askVolList(collectors_list[nb_seed], index->nb_package);
        }

        ++nb_seed;
    } while(*in_buf != '0');

    return nb_seed;
}

void createClientFromIp(Client* client, char* ip){
    struct hostent *h;
    
    *client = initClient();

    if( (h = gethostbyname(ip)) != NULL ) {
        memcpy(&client->sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
    }
    
    client->sock_info.sin_port = htons((in_port_t) COLLECT_PORT);
}

int* findCollVol(Index* index, Collector** coll_list, int nb_seed){
    int i,j;
    
    int* collVol = NULL;
    
    if ( (collVol = malloc(2*sizeof(int))) == NULL ) {
        QUIT_MSG("Can't allocate collVol : ");
    }
    
    collVol[0] = -1;
    collVol[1] = -1;
    
    for(i = 0; i < nb_seed; ++i){
        for(j = 0; j < index->nb_package; ++j){
            if(coll_list[i]->volumes[j] == 1 && index->local_vols[j] == 0){
                collVol[0] = i;
                collVol[1] = j;
                return collVol;
            }
        }
    }
    
    return collVol;
}

void startCollector(char const *index_name){
    int i;
    int nb_seed = 0, nb_leach = 0;

    bool full_file = FALSE;
    fd_set rdfs;
    Client *client = newClientArray(MAX_CONNEXION);
    FILE *file = NULL;
    Index *index = NULL;
    Collector* collectors_list[LIST_COLL_SIZE_MAX];
    
    int seed_socket = initServer();
    int max_socket = seed_socket;
    
    full_file = initIndex(index, index_name, file);
    
    if(!full_file) {
        nb_seed = fillCollectorsList(collectors_list, index);
    }
    
    for ( ;; ) {
        initFd(index, client, nb_leach, &rdfs);
        
        if(!full_file) {          
            getVolume(index, collectors_list, nb_seed, file);
        }
        
        if( (i = select(max_socket + 1, &rdfs, NULL, NULL, NULL)) == -1) {
            endWindows();
            QUIT_MSG("Can't select : ");
        }
        
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;
        }
        else if( FD_ISSET(seed_socket, &rdfs) ) {
            nb_leach += addNewClient(client, seed_socket, &max_socket, nb_leach);
        }
        
        manageClient(client, &nb_leach, & max_socket, index, file, &rdfs);
    }
    
    freeClientArray(client);
    freeIndex(index);
    fclose(file);
}

void initFd(Index* index, Client* client, int nb_leach, fd_set* rdfs){
    int i;
    
    FD_ZERO(rdfs);
    
    FD_SET(STDIN_FILENO, rdfs);
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
                if ( (token = startWith(in_buf, "Vol")) != NULL ) {
                    sendVolume(client_tab[i], atoi(token), index->pack_size, file);
                } else {
                    printf("Oh Mama he send something stupid '%s'", in_buf);
                }
            }
        }
    }
}

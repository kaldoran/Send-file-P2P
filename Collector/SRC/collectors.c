//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include <stdlib.h>
#include <string.h>

#include "tcp.h"
#include "error.h"
#include "socket.h"
#include "client.h"
#include "collectors.h"


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
    struct hostent *h;
    
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
        
        collectors_list[nb_seed]->c = initClient();

        if( (h = gethostbyname(token)) != NULL ) {
            memcpy(&collectors_list[nb_seed]->c.sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
        }
        collectors_list[nb_seed]->c.sock_info.sin_port = htons((in_port_t) COLLECT_PORT);

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

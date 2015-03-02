//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors_list.c                              |
// DATE : 26/02/15                                          |
//----------------------------------------------------------


#include <stdlib.h>
#include <string.h>

#include "tcp.h"
#include "error.h"
#include "client.h"
#include "message.h"
#include "collectors.h"
#include "collectors_list.h"


Collector** newCollectorsList(int nb_coll){
    Collector** collectors_list = (Collector**) calloc(nb_coll, sizeof(Collector*));
    
    return collectors_list;
}

void freeCollectorsList(Collector** coll, int nb_seed) {
    int i;
    for ( i = 0;  i < nb_seed; i++ ) {
        freeCollect(coll[i]);
    }
    
    free(coll);
    return; 
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

Collector** fillCollectorsList(Server* s, Index* index){
    Collector** collectors_list = NULL;
    char in_buf[25] = "";

    char *token;
    struct hostent *h;
    Client tmp = initClient();

    tcpAction(index->c, LIST_OF_COLLECTOR_MSG, sizeof(LIST_OF_COLLECTOR_MSG), SEND);
        
    do {
        memset(in_buf, '\0', 25);

        tcpAction(index->c, in_buf, 25, RECEIVED);
        removeEndCarac(in_buf);
        
        if ( strcmp(in_buf, ALONE_COLLECTOR_MSG) == 0 ) {
            return collectors_list;
        }
        
        token = strtok(in_buf, "|");
        printf("Num of collector : %s\n", token);
        
        if(collectors_list == NULL){
            collectors_list = newCollectorsList( atoi(token) + 1);
        }
        
        token = strtok(NULL, "|");
        printf("Ip of Collector : %s\n", token);
        if( (h = gethostbyname(token)) != NULL ) {
            memcpy(&tmp.sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
        
            token = strtok(NULL, "|");
            printf("Port du collector : %s\n", token);
            tmp.sock_info.sin_port = htons(atoi(token));
                
            if(tcpStart(tmp) == FALSE){
                printf("Can't connect to collector n°%d", s->nb_seed);
            }
            else{
                collectors_list[s->nb_seed] = newCollect(index->nb_package);
                collectors_list[s->nb_seed]->c = tmp;
                
                askVolList(collectors_list[s->nb_seed], index->nb_package);
                ++(s->nb_seed);
            }
        } 
    } while(*in_buf != '0');

    return collectors_list;
}

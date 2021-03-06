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
#include "volume.h"
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

Collector** fillCollectorsList(Server* s, Index* index){
    Collector** collectors_list = NULL;
    char in_buf[COLLECTOR_READER_SIZE] = "";

    char *token;
    struct hostent *h;
    Client tmp = initClient(); 
    #ifdef linux 
        usleep(1);
    #endif //linux
    
    printf("\n[INFO] Ask for other collectors.\n");
    tcpAction(index->c, LIST_OF_COLLECTOR_MSG, sizeof(LIST_OF_COLLECTOR_MSG), SEND);
        
    do {
        memset(in_buf, '\0', COLLECTOR_READER_SIZE);
                
        if ( tcpActionDelay(index->c, in_buf, COLLECTOR_READER_SIZE, S_DELAY, US_DELAY) < 0 ) {
            printf("[ERROR] Client %d does not send information in time\n", index->c.id_socket);
            return collectors_list;
        }
        removeEndCarac(in_buf);
                
        if ( strcmp(in_buf, ALONE_COLLECTOR_MSG) == 0 ) {
            printf("[INFO] We are alone for the moment.\n");
            
            return collectors_list;
        }
        
        token = strtok(in_buf, "|");
        printf("\t - Collector : %s", token);
        
        if(collectors_list == NULL){
            collectors_list = newCollectorsList( atoi(token) + 1);
        }
        
        token = strtok(NULL, "|");
        printf(" [%s:", token);
        if( (h = gethostbyname(token)) != NULL ) {
            memcpy(&tmp.sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
        
            token = strtok(NULL, "|");
            printf("%s]\n", token);
            
            tmp.sock_info.sin_port = htons(atoi(token));
                
            if(tcpStart(tmp) == FALSE){
                printf("[ERROR] Can't connect to collector.\n");
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

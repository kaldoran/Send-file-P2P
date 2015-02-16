//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For fork and kill
#include <string.h>

#include "tcp.h"
#include "error.h"
#include "volume.h"
#include "client.h"
#include "server.h"
#include "boolean.h"
#include "collectors.h"
#include "index_loader.h"
#include "verification.h"
#include "struct_index.h"


void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}


int main(int argc, char const *argv[]) {
    int i;
    int nb_seed = 0, nb_leach = 0;
    char collVol[2];
    bool full_file = FALSE;
    fd_set rdfs;
    struct hostent *h;
    char in_buf[25];
    int total = 0;
    char *token;
    Client *client = newClientArray(MAX_CONNEXION);
    Client tmp;
    FILE *file = NULL;
    Collector* collectors_list[LIST_COLL_SIZE_MAX];
    
    int seed_socket = initServer();
    
    if ( argc < 2 ) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    if( access( argv[1], R_OK|W_OK ) == -1 ) {
        QUIT_MSG("can't acces to : '%s' : ", argv[1]);
    }
    
    Index *index = newIndex();
    if ( loadIndex(argv[1], index) == FALSE ) {
        printf("[ERROR] : Can't reach the boss serveur\n" );
    }
    
    if ( tcpStart(index->c) == FALSE ) {
        QUIT_MSG("Can't connect to boss : ");
    }
    
    char volumes[index->nb_package];
    
    if( access( index->file, R_OK|W_OK ) != -1 ) {
        file = fopen(index->file, "r");
        printf("File exist\n Check integrity\n");
        
        full_file = checkFile(file, index);
    } else {
        file = fopen(index->file, "a+");
        for ( i = 0; i < index->file_size; i++ ) {
            fprintf(file, "#");
        }
        
        memset(index->local_vols, '0', index->nb_package);
    }
    
    if(!full_file) {
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
    }
    
    for ( ;; ) {
        FD_ZERO(&rdfs);
        
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(index->c.id_socket, &rdfs);
        
        if(!full_file) {
            for(i = 0; i < nb_seed; i++) {
                FD_SET(collectors_list[i]->c.id_socket, &rdfs);
            }
            
            getVolume(index, collectors_list, nb_seed, file);
        }
        
        for(i = 0; i < nb_leach; i++) {
            FD_SET(client[i].id_socket, &rdfs);
        }
        
        if( (i = select(max_socket + 1, &rdfs, NULL, NULL, NULL)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;
        }
        else if( FD_ISSET(seed_socket, &rdfs) ) {
            if(nb_leach < MAX_CONNEXION) {
                client[nb_leach] = acceptClient(seed_socket);
                ++nb_leach;
            } else {
                printf("Max number of client reached");
            }
        }
        for(i = 0; i < total; i++) {
            /*
            if(FD_ISSET(client[i].id_socket, &rdfs)) {
                ;
                // one of the personne which you are connect to ask something or send something 
            }
            */    
        }

    }
    
    printf("[[INFO] Client] Welcome to this awesome new project\n");
    
    freeClientArray(client);
    freeIndex(index);
    fclose(file);
    
    exit(EXIT_SUCCESS);
}

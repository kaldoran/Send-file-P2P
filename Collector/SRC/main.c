//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : main.c                                         |
// DATE : 27/01/15                                          |
//----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For fork and kill
#include <string.h>
#include "boolean.h"
#include "struct_index.h"
#include "collectors.h"
#include "index_loader.h"
#include "verification.h"
#include "tcp.h"
#include "error.h"
#include "volume.h"


void usage(const char *name) {
    
    printf("Usage : %s file\n", name);
    
    return;
}


int main(int argc, char const *argv[]) {
    int i;
    fd_set rdfs;
    
    char in_buf[25];
    int total = 0;
    char *token;
    Client *client = newClientArray(MAX_CONNEXION);
    Client tmp;
    FILE *file = NULL;
    Collector* collectors_list[LIST_COLL_SIZE_MAX];
    
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
    
    if( access( index->file, R_OK|W_OK ) != -1 ) {
        file = fopen(index->file, "r");
        printf("File exist\n Check integrity\n");   
        checkFile(file, index);
    }
    else {
        file = fopen(index->file, "a+");
        for ( i = 0; i < index->file_size; i++ ) {
            fprintf(file, "#");
        }
    }

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
        
        collectors_list[i] = newCollect(index->nb_package);
        
        collectors_list[i]->c = initClient();
        strcpy(collectors_list[i]->c.ip, token);
        
        if(tcpStart(collectors_list[i]->c) == FALSE){
            printf("Can't connect to collector n°%d", i);
        }
        else{
            askVolList(collectors_list[i], index->nb_package);
        }
        
        ++total;
    } while(*in_buf != '0');
    
    for ( ;; ) {
        FD_ZERO(&rdfs);
        
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(index->c.id_socket, &rdfs);
        
        for(i = 0; i < total; i++) {
            FD_SET(collectors_list[i]->c.id_socket, &rdfs);
        }
        
        /* Then add the one from accept */
        
        if( (i = select(max_socket + 1, &rdfs, NULL, NULL, NULL)) == -1) {
            QUIT_MSG("Can't select : ");
        }
        
        if( FD_ISSET(STDIN_FILENO, &rdfs) ) {
            break;
        }
        else if( FD_ISSET(server_socket, &rdfs) ) {
            ;
            /* Accept client */
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

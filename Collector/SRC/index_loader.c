//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : chargeur_index.c                               |
// DATE : 31/01/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcp.h"
#include "error.h"
#include "client.h"
#include "boolean.h"
#include "verification.h"
#include "index_loader.h"

char *startWith(char *s1, char *s2) {

    for ( ; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return s2;

    if (*s1 == '\0')
        return s2;
    return NULL;
}

Index *newIndex() {
    Index *index;
    if ((index = calloc(1, sizeof *index)) == NULL) {
        QUIT_MSG("Can't Allocate index");
    }
         
    index->c = initClient();
  
    index->nb_package = -1;
    
    return index;
}

char **newSha(int nb_package) {
    int i;
    char** sha;
    
    if ( (sha = calloc(nb_package, sizeof(char *))) == NULL ) {
        QUIT_MSG("Can't Allocate index->sha");
    }
    
    for ( i = 0; i < nb_package; i++ ) {
        if ( (sha[i] = calloc(41, sizeof(char))) == NULL ) {
            QUIT_MSG("Can't Allocate index->sha[%d]", i);
        }
        memset(sha[i], '\0', 41);
    }
   
    return sha;

}

void freeIndex(Index *index) {
    int i;
        
    for ( i = 0; i < index->nb_package; i++ ) {
        free(index->sha[i]);
    }
    free(index->sha);
    free(index);
}

bool loadIndex(const char *file, Index *index) {
    char i[3] = "0:";
    int j = 0;
    char *ret;
        
    struct hostent *h;
    char ligne_lue[TAILLE_LIGNE];

    FILE* fichier = fopen(file, "r");
    
    while(fgets(ligne_lue, TAILLE_LIGNE, fichier) != NULL){
        
        /* Remove /r and /n */
        if((ret = strchr(ligne_lue, '\r')) != NULL) *ret = '\0'; 
        if((ret = strchr(ligne_lue, '\n')) != NULL) *ret = '\0';

        if ( index->nb_package == -1 ) {
        
            /* complet index */
            if ( (ret = startWith("File:",ligne_lue)) != NULL ) {
                strcpy(index->file, ret);
            }
            else if ( (ret = startWith("Size:", ligne_lue)) != NULL ) {
                index->file_size = atoi(ret);
            }
            else if ( (ret = startWith("PackSize:", ligne_lue)) != NULL ) {
                index->pack_size = atoi(ret);
            }
            else if ( (ret = startWith("NbVolume:", ligne_lue)) != NULL ) {
                index->nb_package = atoi(ret);

                /* Allocate index->sha */
                index->sha = newSha(index->nb_package);
            }
            else if ( (ret = startWith("Boss:",ligne_lue)) != NULL ) { 
                if( (h = gethostbyname(ret)) == NULL ) {
                    return FALSE; /* Can't connect */
                }
                else {
                    memcpy(&index->c.sock_info.sin_addr.s_addr, h->h_addr, h->h_length);
                }
            }    
            else if ( (ret = startWith("Port:",ligne_lue)) != NULL) {
                index->c.sock_info.sin_port = htons((in_port_t)atoi(ret));
            }
            else {
                QUIT_MSG("[Error] Incorrect Index.");
            }
        } 
        else {
            if ( (ret = startWith(i, ligne_lue)) != NULL) {
                j = i[0] - '0';
                memcpy(index->sha[j], ret, 41);
                i[0]++;
            }
        }
    }
    
    if ((index->local_vols = calloc(index->nb_package, sizeof(char))) == NULL) {
        QUIT_MSG("Can't Allocate index");
    }

    fclose(fichier);
    return TRUE;
}

bool initFile(Index* index, FILE* file){
    bool full_file = FALSE;
    int i;
    
    if( fileExist(index->file) ) {
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
    
    fclose(file);
    file = fopen(index->file, "r+");
    
    return full_file;
}

bool initIndex(Index* index, char const *index_name, FILE* file){
    index = newIndex();
    
    if ( loadIndex(index_name, index) == FALSE ) {
        printf("[ERROR] : Can't reach the boss serveur\n" );
    }
    
    if ( tcpStart(index->c) == FALSE ) {
        QUIT_MSG("Can't connect to boss : ");
    }

    return TRUE;
}


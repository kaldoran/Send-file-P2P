//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : chargeur_index.c                               |
// DATE : 31/01/15                                          |
//----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boolean.h"
#include "index_loader.h"
#include "error.h"

char *startWith(char *s1, char *s2) {

	for ( ; *s1 == *s2; s1++, s2++)
		if (*s1 == '\0')
			return s2;

	if (*s1 == '\0')
		return s2;
	return NULL;
}

Index *new_index() {
	Index *index;
	if ((index = calloc(1, sizeof *index)) == NULL) {
		QUIT_MSG("Can't Allocate index");
	}
	
	index->nbPackage = -1;
	
	return index;
}

unsigned char **new_sha(int nbPackage) {
	int i;
	unsigned char** sha;
	
	if ( (sha = calloc(nbPackage, sizeof(unsigned char *))) == NULL ) {
		QUIT_MSG("Can't Allocate index->sha");
	}
	
	for ( i = 0; i < nbPackage; i++ ) {
		if ( (sha[i] = calloc(40, sizeof(unsigned char))) == NULL ) {
			QUIT_MSG("Can't Allocate index->sha[%d]", i);
		}
	}
	return sha;

}

void free_index(Index *index) {
	int i;
	
	for ( i = 0; i < index->nbPackage; i++ ) {
		free(index->sha[i]);
	}
	free(index->sha);
	free(index);
}

bool charger_index(const char *file, Index *index) {
	char i[2] = "1:";
	int j = 0;
	char *ret;
	
	struct hostent *h;
	char ligne_lue[TAILLE_LIGNE];

	FILE* fichier = fopen(file, "r");
	while(fgets(ligne_lue, TAILLE_LIGNE, fichier) != NULL){

		/* Remove /r and /n */
		if((ret = strchr(ligne_lue, '\r')) != NULL) *ret = '\0'; 
		if((ret = strchr(ligne_lue, '\n')) != NULL) *ret = '\0';

		if ( index->nbPackage == -1 ) {
		
			/* complet index */
			if ( (ret = startWith("File:",ligne_lue)) != NULL ) {
				strcpy(index->file, ret);
			}
			else if ( (ret = startWith("Size:", ligne_lue)) != NULL ) {
				index->fileSize = atoi(ret);
			}
			else if ( (ret = startWith("PackSize:", ligne_lue)) != NULL ) {
				index->packSize = atoi(ret);
			}
			else if ( (ret = startWith("NbVolume:", ligne_lue)) != NULL ) {
				index->nbPackage = atoi(ret);

				/* Allocate index->sha */
				index->sha = new_sha(index->nbPackage);
			}
			else if ( (ret = startWith("Boss:",ligne_lue)) != NULL ) { 
				if( (h = gethostbyname(ret)) == NULL ) {
					return FALSE; /* Can't connect */
				}
				else {
					memcpy(&index->ip, h->h_addr, h->h_length);
				}
			}	
			if ( (ret = startWith("Port:",ligne_lue)) != NULL) {
				index->port = htons((in_port_t)atoi(ret));
			}
		} 
		else {
			if ( (ret = startWith(i, ligne_lue)) != NULL) {
				j = i[0] - '0';
				memcpy(index->sha[--j], ret, 40);
				i[0]++;
			}
		}
	}

	fclose(fichier);
	return TRUE;
}


//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.c                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include "volume.h"

void getVolume(int volNum, int volSize, Collector* collectors, FILE* file){
    (void) collectors; 
    char read[volSize];

    int collector; /* Collector with searched volume's socket id */
    recv(collector, read, volSize, 0);
    
    fseek(file, (volSize*volNum-1), SEEK_SET);
        
    fprintf(file, "%s", read);
}

void sendVolume(Socket *s, int volNum) {
    (void) s;
    (void) volNum;
}
//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.c                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include "volume.h"
#include "tcp.h"

void getVolume(int volNum, int volSize, Collector* collectors, FILE* file) {
    (void) collectors; 
    char read[volSize];

    // int collector; /* Collector with searched volume's socket id */
    
    //tcp_action(collector, read, volSize, RECEIVED);
    
    fseek(file, (volSize * volNum ), SEEK_SET);
        
    fprintf(file, "%s", read);
}

void sendVolume(Socket *s, int volNum, int volSize, FILE* file) {
    
    char buf[volSize];
    
    fseek(file, ( volSize * volNum ), SEEK_SET);
    fread ((char*)buf, volSize, 1, file);
       
    tcp_action(s, buf, volSize, SEND);
}
//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.c                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#include "volume.h"
#include "tcp.h"

void getVolume(int vol_num, int vol_size, Collector* collectors, FILE* file) {
    (void) collectors; 
    char read[vol_size];

    // int collector; /* Collector with searched volume's socket id */
    
    //tcp_action(collector, read, volSize, RECEIVED);
    
    fseek(file, (vol_size * vol_num ), SEEK_SET);
        
    fprintf(file, "%s", read);
}

void sendVolume(Client c, int vol_num, int vol_size, FILE* file) {
    
    char buf[vol_size];
    
    fseek(file, ( vol_size * vol_num ), SEEK_SET);
    fread ((char*)buf, vol_size, 1, file);
       
    tcpAction(c, buf, vol_size, SEND);
}
//----------------------------------------------------------
// AUTEUR : BASCOL Kevin                                    |
// FICHIER : collectors.c                                   |
// DATE : 08/02/15                                          |
//----------------------------------------------------------


#include "collectors.h"


Collector* new_collect(int nb_vol, char* ip_coll){
    Collector* collect;
    
    if ((collect = calloc(1, sizeof *collect)) == NULL) {
        QUIT_MSG("Can't Allocate Collector");
    }
    
    collect->sock = new_socket();
    
    if ((collect->volumes = calloc(nb_vol, sizeof char)) == NULL) {
        QUIT_MSG("Can't Allocate Collector's volume list");
    }
    
    collect->nb_volumes = nb_vol;
    
    return collect;
}

void ask_vol_list(Collector* collect){
    
}

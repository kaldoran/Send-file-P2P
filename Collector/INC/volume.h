//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.h                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#ifndef VOLUME_H
#define VOLUME_H

#include <stdio.h>

#include "socket.h"
#include "struct_collect.h"

void getVolume(int vol_num, int vol_size, Collector* collectors, FILE* file);

void sendVolume(SOCKET s, int volNum, int vol_size, FILE* file);

#endif /* VOLUME_H included */
//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.h                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#ifndef VOLUME_H
#define VOLUME_H

#include <stdio.h>

#include "struct_socket.h"
#include "struct_collect.h"

void getVolume(int volNum, int volSize, Collector* collectors, FILE* file);

void sendVolume(Socket *s, int volNum, int volSize, FILE* file);

#endif /* VOLUME_H included */
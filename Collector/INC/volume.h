//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas & BASCOL Kevin                  |
// FICHIER : volume.h                                       |
// DATE : 08/02/15                                          |
//----------------------------------------------------------
#include <stdio.h>

#include "struct_socket.h"
#include "struct_collect.h"

void getVolume(int volNum, int volSize, Collector* collectors, FILE* file);

void sendVolume(Socket *s, int volNum);
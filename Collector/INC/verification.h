//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : verification.h                                 |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <stdio.h>
#include <openssl/sha.h>

#include "boolean.h"
#include "struct_index.h"


void hexToString(unsigned char outbuf[SHA_DIGEST_LENGTH], char outsha[40]);

bool checkFile(FILE* file, Index* index);

bool checkVol(Index* index, unsigned char* vol, int id_vol);

#endif /* VERIFICATION_H included */

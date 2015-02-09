//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : verification.h                                 |
// DATE : 08/02/15                                          |
//----------------------------------------------------------

#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <stdlib.h>
#include <openssl/sha.h>

#include "struct_index.h"


void hexToString(unsigned char outbuf[SHA_DIGEST_LENGTH], char outsha[40]);

void checkFile(FILE* file, Index* index);

#endif /* VERIFICATION_H included */
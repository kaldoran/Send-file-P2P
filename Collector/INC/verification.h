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

/** Translates a hexadecimal sha1 to a characters sha1.
 * 
 *  %param outbuf: Hexadecimal sha1.
 *  %param outsha: Characters sha1.
 */
void hexToString(unsigned char outbuf[SHA_DIGEST_LENGTH], char outsha[40]);

/** Verifies the checksums of a file comprared to the index.
 * 
 *  %param file: Pointer to the file.
 *  %param index: Pointer to the loaded Index.
 * 
 *  %return : TRUE if the file is complete and its volumes checked,
 *            FALSE otherwise.
 */
bool checkFile(FILE* file, Index* index);


/** Verifies the checksum of a volume comprared to the index.
 * 
 *  %param index: Pointer to the loaded Index.
 *  %param vol: Volume to check.
 *  %param id_vol: Number of the volume in the Index.
 * 
 *  %return: TRUE if the volume corresponds to the checksum,
 *           FALSE otherwise.
 */
bool checkVol(Index* index, unsigned char* vol, int id_vol);

bool fileExist(const char *filename);

#endif /* VERIFICATION_H included */

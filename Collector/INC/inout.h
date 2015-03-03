//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : inout.h                                        |
// DATE : 03/03/15                                          |
//----------------------------------------------------------

#ifndef INOUT_H
#define INOUT_H

/** Ask the user which ndex to use
 *  %return : name of the ndex file
 */
char* askNDex();

/** Ask the user the port
 *  %return : Which port to use
 */
int askPort();

/** Function to empty the stdin buffer.
 */
void emptyBuffer();

#endif /* INOUT_H included */
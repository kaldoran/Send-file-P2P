//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : inout.h                                        |
// DATE : 03/03/15                                          |
//----------------------------------------------------------

#ifndef INOUT_H
#define INOUT_H

/** Asks the user which ndex to use
 *  %return : name of the ndex file
 */
char* askNDex();

/** Asks the user the port
 *  %return : Which port to use
 */
int askPort();

/** Asks and creates the repository that the user use to share.
 *  %return : the sharing path to create
 */
char* askShareRepo();

/** Function to empty the stdin buffer.
 */
void emptyBuffer();

/** Creates all subdirectories in the given path.
 *  %param dir: Repository to create.
 */
void mkdirRec(const char *dir);

#endif /* INOUT_H included */

//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : inout.h                                            |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#ifndef INOUT_H
#define INOUT_H

/** Function to ask the boss' ip for an index.
 *  %return : Boss' IP adress.
 */
char* askBossIp();

/** Function to ask the boss' port for an index.
 *  %return : Boss' port.
 */
int askBossPort();

/** Function to ask the volumes' size for an index.
 *  %return : Volumes' size.
 */
int askVolSize();

/** Function that ask which file we want to create the .ndex
 *  %return : name of the file 
 */
char* askFile();
/** Function to empty the stdin buffer.
 */
void emptyBuffer();

#endif /* INOUT_H included */

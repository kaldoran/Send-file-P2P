//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : inout.h                                            |
// DATE : 30/01/15                                           |
//----------------------------------------------------------


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

/** Function to empty the stdin buffer.
 * 
 */
void emptyBuffer();

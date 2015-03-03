//----------------------------------------------------------
// AUTHOR : REYNAUD Nicolas                                 |
// FILE : file.h                                            |
// DATE : 28/01/15                                          |
//----------------------------------------------------------

#ifndef FILE_H
#define FILE_H

/** Function that create the ndex corresponding to is parameter 
 *  %param ip : Ip of the boss
 *  %param port : Port of the boss
 *  %param packSize : Size of the package / volume
 *  %param filename : Name of the file which on why generate the ndex
 *  %param buf : Stats of the file
 */
void createNDex(char* ip, int port, int packSize, char* fileName, struct stat buf);

#endif /* FILE_H included */

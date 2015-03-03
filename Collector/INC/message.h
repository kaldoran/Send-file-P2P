//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : message.h                                      |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#ifndef MESSAGE_H
#define MESSAGE_H

#define READER_SIZE 50
#define COLLECTOR_READER_SIZE 30

#define ALONE_COLLECTOR_MSG "aloneCollector"
#define FILE_EXIST_MSG "exist"
#define FILE_NOT_EXIST_MSG "notExist"
#define PREFIX_OF_VOLUME_MSG "Vol"
#define LIST_OF_VOLUMES_MSG "ListOfVolumes"
#define LIST_OF_COLLECTOR_MSG "ListOfCollectors"


/** Remove the end caractere of a string 
 *  Remove : \n and \r
 *  %param input : string where you need to remove caractere 
 */
void removeEndCarac(char *input);

#endif /* MESSAGE_H included */

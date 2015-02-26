//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : message.h                                      |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#ifndef MESSAGE_H
#define MESSAGE_H

#define READER_SIZE 80

#define FILE_EXIST_MSG "exist"
#define FEM_SIZE 5

#define FILE_NOT_EXIST_MSG "notExist"
#define FNEM_SIZE 8

#define PREFIX_OF_VOLUME_MSG "Vol"

#define LIST_OF_VOLUMES_MSG "ListOfVolumes"
#define LOVM_SIZE 13

#define LIST_OF_COLLECTOR_MSG "ListOfCollectors"
#define LOCM_SIZE 16

/** Remove the end caractere of a string 
 *  Remove : \n and \r
 *  %param input : string where you need to remove caractere 
 */
void removeEndCarac(char *input);

#endif /* MESSAGE_H included */

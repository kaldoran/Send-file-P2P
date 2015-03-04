//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : message.h                                      |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#ifndef MESSAGE_H
#define MESSAGE_H

#include "struct_block_group.h"

#define READER_SIZE 50

#define ALONE_COLLECTOR_MSG "aloneCollector"
#define FILE_EXIST_MSG "exist"
#define FILE_NOT_EXIST_MSG "notExist"
#define LIST_OF_COLLECTOR_MSG "ListOfCollectors"

/** Remove the end caractere of a string 
 *  Remove : \n and \r
 *  %param input : string where you need to remove caractere 
 */
void removeEndCarac(char *input);

bool handlerUserInput(blockGroup* block_group);

#endif /* MESSAGE_H included */

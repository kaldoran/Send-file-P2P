//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : message.h                                      |
// DATE : 21/02/15                                          |
//----------------------------------------------------------

#ifndef MESSAGE_H
#define MESSAGE_H

#include "struct_block_group.h"

#define READER_SIZE 80

#define FILE_EXIST_MSG "exist"
#define FILE_NOTEXIST_MSG "notExist"
#define LIST_OF_COLLECTOR_MSG "ListOfCollectors"

void removeEndCarac(char *input);

void handlerMessage(blockGroup* block_group, char inBuf[READER_SIZE], int tmpVal);

#endif /* MESSAGE_H included */
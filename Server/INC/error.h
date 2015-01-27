//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : error.h                                        |
// DATE : 27/01/15                                          |
//                                                          |
// - Debug Maccro [C99 Convention]                          |
// - Quit maccro                                            |
//----------------------------------------------------------

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/** If Debug Flag is on, create a maccro to print debug information
 *  %param MSG : String to print 
 *  %param ... : List of param [ for example if want to print variable value ]
 */
#ifdef DEBUG
    #define DEBUG_PRINTF(MSG, ...)                                                                                          \
    do {                                                                                                                    \
        fprintf(stderr, "\n\t[DEBUG] File : %s - Line : %d - Function : %s() : " MSG "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__);    \
    } while(0);
#else
    #define DEBUG_PRINTF(MSG, ...)
#endif


/** Create a maccro for quit the program 
 *  %param MSG : String to print 
 *  %param ... : List of param [ for example if want to print variable value ]
 */
#define QUIT_MSG(MSG, ...)                                                                                                  \
    do {                                                                                                                    \
        DEBUG_PRINTF(MSG, ##__VA_ARGS__)                                                                                    \
        fprintf(stderr, "[FATAL ERROR] : ");                                                                                \
        fprintf(stderr, MSG, ## __VA_ARGS__);                                                                               \
        exit(EXIT_FAILURE);                                                                                                 \
    }while(0);

#endif /* ERROR_H included */

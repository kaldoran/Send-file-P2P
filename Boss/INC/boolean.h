//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : boolean.h                                      |
// DATE : 28/01/15                                          |
//----------------------------------------------------------

#ifndef BOOLEAN_H
#define BOOLEAN_H

#define FALSE 0
#define TRUE !FALSE /* True is the invert of False */

/** Define what is a boolean
 *  'false' is equal to 0 by default.
 */
typedef enum {
    false = 0,
    true
} bool;

#endif /* BOOLEAN_H included */
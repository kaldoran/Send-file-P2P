//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : verification.h                                     |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#ifndef VERIFICATION_H
#define VERIFICATION_H

#include "boolean.h"


/**	Funtion to verify the user imput for the boss' IP.
 *  %param ip : IP to verify.
 *  %return : If valid IP then TRUE, else FALSE.
 */
bool verifBossIp(char* ip);

/**	Funtion to verify the user imput for the boss' port.
 *  %param port : Port to verify.
 *  %return : If valid port then TRUE, else FALSE.
 */
bool verifBossPort(int port);

/**	Funtion to verify the user imput for the volumes' size.
 *  %param size : Size to verify.
 *  %return : If valid size then TRUE, else FALSE.
 */
bool verifVolSize(int size);

/** Function to test if the string match the regex.
 *  %param regex : Regular expression to match to.
 *  %param string : String to test.
 */
bool testRegex(char* regex, char* string);

#endif /* VERIFICATION_H included */
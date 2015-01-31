//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : verification.c                                     |
// DATE : 30/01/15                                           |
//----------------------------------------------------------

#include <stdio.h>
#include <regex.h>

#include "verification.h"

bool verifBossIp(char* ip){
    return testRegex("^([0-9]{1,3}.){3}[0-9]{1,3}$", ip);
}

bool verifBossPort(int port) {
	if(port <= 1024){
		printf("The port must be greater than 1024\n");
	}
	else if(port > 65536) {
		printf("The port must be lower than 65536\n");
	}
	else {
		return TRUE;
	}
	return FALSE;
}

bool verifVolSize(int size){
	if(size < 8){
		printf("The volumes' size must be greater than 8ko\n");
	}
	else if(size > 64) {
		printf("The volumes' size must be lower than 64ko\n");
	}
	else {
		return TRUE;
	}
	return FALSE;
}

bool testRegex(char* regex, char* string) {
    regex_t preg;
    bool valid = FALSE;

    if(regcomp(&preg, regex, REG_NOSUB | REG_EXTENDED) == 0) {
        if(regexec (&preg, string, 0, NULL, 0) == 0) {
            valid = TRUE;
        }
    }
    
    regfree(&preg);
    return valid;
}
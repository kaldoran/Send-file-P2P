//----------------------------------------------------------
// AUTHOR : BASCOL Kevin                                     |
// FILE : verification.c                                     |
// DATE : 30/01/15                                           |
//----------------------------------------------------------



bool verifIpBoss(char* ip){
    return testRegex("^([0-9]{1,3}.){3}[0-9]{1,3}$", ip);
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

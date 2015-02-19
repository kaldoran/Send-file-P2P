//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : windows.c                                      |
// DATE : 19/02/15                                          |
//----------------------------------------------------------

void initWindows(void) {
    #ifdef WIN32
       WSADATA wsa;
       int err = WSAStartup(MAKEWORD(2, 2), &wsa);
       if(err < 0) {
          QUIT_MSG("Can't start socket on Windaube : ");
       }
    #endif
}

void endWindows(void) {
    #ifdef WIN32
       WSACleanup();
    #endif
}   

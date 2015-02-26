//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : windows.c                                      |
// DATE : 19/02/15                                          |
//----------------------------------------------------------

#include "windows.h"
#include "socket.h"
#include "error.h"

#ifdef WIN32
    #pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

void initWindows(void) {
    #ifdef WIN32
       WSADATA wsa;
       if(WSAStartup(MAKEWORD(2, 2), &wsa) < 0) {
          QUIT_MSG("Can't start socket on Windaube : ");
       }
    #endif
}

void endWindows(void) {
    #ifdef WIN32
       WSACleanup();
    #endif
}   

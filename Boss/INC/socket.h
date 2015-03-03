//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : socket.h                                       |
// DATE : 15/02/15                                          |
//----------------------------------------------------------

#ifndef SOCKET_H
#define SOCKET_H

/* If We are on windows */
#include <unistd.h>
    
    #if defined (WIN32)
        #include <winsock2.h>
    #elif defined (linux)

        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <netdb.h>

        #define INVALID_SOCKET -1
        #define SOCKET_ERROR -1
        #define closesocket(s) close (s)

        typedef int SOCKET;
        typedef struct sockaddr_in SOCKADDR_IN;
        typedef struct sockaddr SOCKADDR;

    #endif

#endif /* SOCKET_H included */
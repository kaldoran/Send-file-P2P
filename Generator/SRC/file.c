//----------------------------------------------------------
// AUTHOR : REYNAUD Nicolas                                 |
// FILE : file.c                                            |
// DATE : 28/01/15                                          |
//----------------------------------------------------------

#include <libgen.h>
#include <sys/stat.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <openssl/sha.h>

#include "file.h"
#include "error.h"


void createNDex(char* ip, int port, int packSize, char* fileName, struct stat buf) {

    int i, j;
    int nbVolume;
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    unsigned char inbuf[packSize];
    unsigned char outbuf[SHA_DIGEST_LENGTH];
    char *baseName = basename(fileName);
    char outputName[FILENAME_MAX] = "";
    
    if ( (inputFile = fopen(fileName, "r")) == NULL) {
        QUIT_MSG("Opening file '%s'", fileName);
    }
    
    sprintf(outputName, "%s.ndex", baseName);
    if ( (outputFile = fopen(outputName, "w+")) == NULL ) {
        QUIT_MSG("Opening file '.ndex'");
    }
    
    nbVolume = floor(buf.st_size / packSize) + 1;

    printf("\n[INFO] Boss : %s\n", ip);
    printf("[INFO] Port : %d\n", port);
    printf("[INFO] File : %s\n", baseName);
    printf("[INFO] Size : %ld Octets\n", buf.st_size);
    printf("[INFO] PackSize : %d\n", packSize);
    printf("[INFO] NbVolume : %d\n", nbVolume);
    
    fprintf(outputFile, "Boss:%s\n", ip);
    fprintf(outputFile, "Port:%d\n", port);
    fprintf(outputFile, "File:%s\n", baseName);
    fprintf(outputFile, "Size:%ld\n", buf.st_size);
    fprintf(outputFile, "PackSize:%d\n", packSize);
    fprintf(outputFile, "NbVolume:%d\n", nbVolume);
    
    for ( i = 0; i < nbVolume; ) {
        
        memset(inbuf, '\0', packSize); 
        
        fread ((char*)inbuf, packSize, 1, inputFile);

        SHA1(inbuf, sizeof(inbuf), outbuf);

        printf("[INFO] Volume %d\n\tSha1 : ", i);
        fprintf(outputFile, "%d:", i);
        
        for(j = 0; j < SHA_DIGEST_LENGTH; j++) {
            printf("%02x", outbuf[j]);
            fprintf(outputFile, "%02x", outbuf[j]);
        }

        printf("\n");
        if ( ++i != nbVolume ) {
            fprintf(outputFile, "\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    
    printf("\n[INFO] : File '%s' had been generated\n", outputName);
    
    return;
}

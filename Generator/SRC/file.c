//----------------------------------------------------------
// AUTHOR : REYNAUD Nicolas                                 |
// FILE : file.c                                            |
// DATE : 28/01/15                                          |
//----------------------------------------------------------

#include <libgen.h>
#include <sys/stat.h>
#include <stdio.h>
#include <math.h>
#include <openssl/sha.h>

#include "file.h"
#include "error.h"

void createNDex(char* ip, int port, int packSize, char* fileName) {
    struct stat buf;
    int i, j;
    int nbVolume;
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    unsigned char inbuf[packSize];
    unsigned char outbuf[SHA_DIGEST_LENGTH];
    char *baseName = basename(fileName);
    
    
    if ( stat(fileName, &buf) == -1 ) {
        QUIT_MSG("Can't stats %s", fileName);
    }
    
    if ( (inputFile = fopen(fileName , "r")) == NULL) {
        QUIT_MSG("Opening file '%s'", fileName);
    }
    
    if ( (outputFile = fopen(".ndex", "w+")) == NULL ) {
        QUIT_MSG("Opening file '.ndex'");
    }
    
    nbVolume = floor(buf.st_size / packSize) + 1;


    printf("Boss:%s\n", ip);
    printf("Port:%d\n", port);
    printf("File:%s\n", baseName);
    printf("Size:%ld\n", buf.st_size);
    printf("PackSize:%d\n", packSize);
    printf("NbVolume:%d\n", nbVolume);
    
    fprintf(outputFile, "Boss:%s\n", ip);
    fprintf(outputFile, "Port:%d\n", port);
    fprintf(outputFile, "File:%s\n", baseName);
    fprintf(outputFile, "Size:%ld\n", buf.st_size);
    fprintf(outputFile, "PackSize:%d\n", packSize);
    fprintf(outputFile, "NbVolume:%d\n", nbVolume);
    
    for ( i = 1; i <= nbVolume; i++ ) {
        
        fread ((char*)inbuf, packSize, 1, inputFile);

        SHA1(inbuf, sizeof(inbuf), outbuf);

        printf("%d:", i);
        fprintf(outputFile, "%d:", i);
        
        for(j = 0; j < SHA_DIGEST_LENGTH; j++) {
            printf("%02x", outbuf[j]);
            fprintf(outputFile, "%02x", outbuf[j]);
        }

        printf("\n");
        if ( i != nbVolume ) {
            fprintf(outputFile, "\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    
    
    printf("\n[INFO] : File '.ndex' add been generated\n");
    
    
    return;
}

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

void createNDex(char* ip, int port, long long packSize, char* fileName) {
	struct stat buf;
	int i, j;
	int nbVolume;
	FILE *intputFile = NULL;
	FILE *outputFile = NULL;
	unsigned char inbuf[packSize];
	unsigned char outbuf[SHA_DIGEST_LENGTH];
	char *baseName = basename(fileName);
	
	
	if ( stat(fileName, &buf) == -1 ) {
		QUIT_MSG("Can't stats %s", fileName);
	}
	
	if ( (intputFile = fopen(fileName , "r")) == NULL) {
		QUIT_MSG("Opening file '%s'", fileName);
	}
	
	if ( (outputFile = fopen(".ndex", "w+")) == NULL ) {
		QUIT_MSG("Opening file '.ndex'");
	}
	
	nbVolume = floor(buf.st_size / packSize) + 1;

	DEBUG_PRINTF("Boss:%s\n", ip);
	DEBUG_PRINTF("Port:%d\n", port);
	DEBUG_PRINTF("File:%s\n", baseName);
	DEBUG_PRINTF("Size:%lld\n", (long long)buf.st_size);
	DEBUG_PRINTF("PackSize:%lld\n", packSize);
	DEBUG_PRINTF("NbVolume:%d\n", nbVolume);
	
	fprintf(outputFile, "Boss:%s\n", ip);
	fprintf(outputFile, "Port:%d\n", port);
	fprintf(outputFile, "File:%s\n", baseName);
	fprintf(outputFile, "Size:%lld\n", (long long)buf.st_size);
	fprintf(outputFile, "PackSize:%lld\n", packSize);
	fprintf(outputFile, "NbVolume:%d\n", nbVolume);
	
	for ( i = 1; i <= nbVolume; i++ ) {
	 	if ( fgets ((char*)inbuf, packSize, intputFile) != NULL ) {
			SHA1(inbuf, sizeof(inbuf), outbuf);

			DEBUG_PRINTF("%d:", i);
			fprintf(outputFile, "%d:", i);
			
			for(j = 0; j < SHA_DIGEST_LENGTH; j++) {
				DEBUG_PRINTF("%02x", outbuf[j]);
				fprintf(outputFile, "%02x", outbuf[j]);
			}

			if ( i != nbVolume ) {
				DEBUG_PRINTF("\n");
				fprintf(outputFile, "\n");
			}
		}
	}
	
	fclose(intputFile);
	fclose(outputFile);
	
	
	printf("File '.ndex' add been generated\n");
	
	
	return;
}

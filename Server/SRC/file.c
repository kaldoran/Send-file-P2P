//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : file.c                                         |
// DATE : 28/01/15                                          |
//----------------------------------------------------------


#include <libgen.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

#include "error.h"
#include "file.h"


bool checkFileExist(char *file) {
	bool output = FALSE;
	DIR* dir = NULL;
	struct dirent* currentFile = NULL;
	char *baseName = basename(file);
	char *dirName = dirname(file);
	
	dir = opendir(dirName);
	if ( dir == NULL ) {
		errno = ENOENT;
		QUIT_MSG("Can't access to '%s' : ", dirName);
	}
	
	while ( output == FALSE && (currentFile = readdir(dir)) != NULL ) {
		if ( strcmp(currentFile->d_name, baseName) == 0) {
			output = TRUE;
		}
	}
	
	closedir(dir);
	
	return output;

}


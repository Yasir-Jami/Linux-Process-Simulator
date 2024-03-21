#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "findme.h"

void sprint(char* pathname, char* type, int);



int main(int argc, char* argv[]){
	// Require pathname
	if (argc < 2){
		printf("Usage: findme --type [arg] --name [arg] --user [arg] --maxdepth [arg]\n");
		exit(EXIT_FAILURE);
	}

	// Arg defaults
	//char* pathname = argv[1];; // current directory

	char* pathname = ".";
	char* type = "f"; // File type: f - reg, d - dir, etc. - set to 0 by default to look for all file types

	/*
	char* name = "0"; // Specified filename
	char* user = "jamiy2"; // User name*/
	int maxdepth = 10; // Height of directory search to look through


	sprint(pathname, type,maxdepth);



	/*
	printf("\nCurrent type: %s\n", type);
	printf("Current name: %s\n", name);
	printf("Current user: %s\n", user);
	printf("Current maxdepth: %d\n", maxdepth);
	*/

	return 0;
}

void sprint(char* pathname, char* type, int depth){
	if (depth == 0) {
		return;
	}
	struct stat buf;
	DIR *dir;
//	DIR *currentdir;
	struct dirent *file;
	char fileloc[100];
	int argtype = getFileArgType(*type);
	dir = opendir(pathname);

	if (dir == NULL) {
		printf("Not a valid dir. Closing program\n");
		exit(EXIT_FAILURE);
	}

	while((file = readdir(dir))) {
		if ((strcmp(file->d_name,".") == 0) || (strcmp(file->d_name, "..")==0)) {
			continue;
		}
		strcpy(fileloc,pathname);
		strncat(fileloc,"/",2);
		strncat(fileloc, file->d_name, 100);
		stat(fileloc,&buf);
		if (getFileType(fileloc)==1) {
			sprint(fileloc, type, depth-1);
		}
		if (getFileType(fileloc) == argtype || argtype == -1) {
			printf("%s\n", fileloc);
		}

	}
	closedir(dir);
}



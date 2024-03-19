#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "findme.h"

int main(int argc, char* argv[]){	
	// Require pathname
	if (argc < 2){
		printf("Usage: findme -type [arg] -name [arg] -user [arg] -maxdepth [arg]\n");
		exit(EXIT_FAILURE);
	}
	// Arg defaults
	//char* pathname = argv[1];; // current directory
	char* pathname = ".";
	char* type = "f"; // regular file - change to any kind of file
	char* name = "default"; // any filename
	char* user = "jamiy2"; // my username
	int maxdepth = 1; // Look only one directory deep

	parseCommands(argc, argv, &type, &name, &user, &maxdepth);
	// Check for path validity
	DIR* dir = opendir(pathname);
	closedir(dir);
	
	printf("\nCurrent type: %s\n", type);
	printf("Current name: %s\n", name);
	printf("Current user: %s\n", user);
	printf("Current maxdepth: %d\n", maxdepth);

	// Will use the order:
	// 0 - Regular file 
	// 1 - Directory
	// 2 - Symbolic Link
	// 3 - Block Device
	// 4 - Character Device	

	return 0;
}


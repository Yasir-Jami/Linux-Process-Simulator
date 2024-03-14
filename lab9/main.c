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
		printf("Usage: findme [type] [name] [user] [maxdepth] \n");	
		exit(EXIT_FAILURE);
	}
	// Arg defaults
	//char* pathname = argv[1];; // current directory
	char* pathname = ".";
	char* type = "f"; // regular file
	char* name = "*"; // any file - kind of essential though, so maybe I should stop the program if it is not provided
	char* user = "jamiy2"; // my username
	int maxdepth = 1; // Look only one directory deep	

	//parseCommand(argc, argv, &type, &name, &user, &maxdepth);
	DIR* dir = opendir(pathname);
	closedir(dir);
		
	// Will use the order:
	// 0 - Regular file 
	// 1 - Directory
	// 2 - Symbolic Link
	// 3 - Block Device
	// 4 - Character Device	

	return 0;
}


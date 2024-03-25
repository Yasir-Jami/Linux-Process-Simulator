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
		printf("Usage: findme [directory] Options: -type [f,d,s,c,b] -name [filename] -user [username] -maxdepth [0-*]\n");
		exit(EXIT_FAILURE);
	}
	char* pathname;	// argv[1]
	char* type; // File type to look for
	char* name; // Specified file name
	char* user; // Owner of file
	int maxdepth; // Height of directory search

	pathname = argv[1];
	type = ""; // File type: f - reg, d - dir, etc. - set to 0 by default to look for all file types
	name = "0"; 
	user = ""; 
	maxdepth = 255; 

	// Get arguments from command line, if there are any
	parseCommands(argc, argv, &type, &name, &user, &maxdepth);
	// Prints all directories
	dirprint(pathname, type, name, user, maxdepth);

	/*	
	printf("Current type: %s\n", type);
	printf("Current file name: %s\n", name);
	printf("Current user: %s\n", user);
	printf("Current maxdepth: %d\n", maxdepth);
	*/

	return 0;
}

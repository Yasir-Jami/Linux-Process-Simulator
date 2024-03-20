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
		printf("Usage: findme --type [arg] --name [arg] --user [arg] --maxdepth [arg]\n");
		exit(EXIT_FAILURE);
	}
	
	// Arg defaults
	//char* pathname = argv[1];; // current directory
	
	char* pathname = ".";
	char* type = "f"; // File type: f - reg, d - dir, etc. - set to 0 by default to look for all file types
	/*
	char* name = "0"; // Specified filename
	char* user = "jamiy2"; // User name 
	int maxdepth = 1; // Height of directory search to look through
	*/

	//parseCommands(argc, argv, &type, &name, &user, &maxdepth);
	
	// Check for path validity
	struct stat buf; // stat.h pointer used to determine a file's stats 
	DIR *dir; // Pointer to origin directory - provided by user or current directory by default
	DIR *currentdir; // Pointer to current directory being examined	
	struct dirent *file; // Pointer to current file being examined
	char fileloc[100]; // Name of file being examined
	int argtype = getFileArgType(*type); // int representing file type

	// Open origin path
	dir = opendir(pathname);
	if (dir == NULL){
		printf("Not a valid directory. Closing program.\n");
		exit(EXIT_FAILURE);
	}

	/*
	readdir(DIR *) - reads the content of a directory and returns an object of type dirent (struct)	
	*/

	// Need to check file type before printing
	// Search through all directories according to specified maxdepth; set to 255 by default
	// Recursive search - search through the first encounter directory, print all contents, go to next directory, print, etc.
	while ((file = readdir(dir))){
		if ((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name, "..") == 0)){
			continue;
		} 
		// Need to print file location in the form (origin_path_of_directory)/(FILE)
		// So keep appending file directories until reaching the file
		strcpy(fileloc, pathname);
	        strncat(fileloc, "/", 2);
		strncat(fileloc, file->d_name, 100);
		stat(fileloc, &buf);
	
		// If chosen file's type matches the chosen -type argument or if there is no -type arg specified, print the path
		if (getFileType(fileloc) == argtype || argtype == -1){
			// Point to file - goes to next file if file is not of the type being examined
			printf("%s\n", fileloc);
		}
	}
	closedir(dir);	

	/*
	printf("\nCurrent type: %s\n", type);
	printf("Current name: %s\n", name);
	printf("Current user: %s\n", user);
	printf("Current maxdepth: %d\n", maxdepth);
	*/

	return 0;
}

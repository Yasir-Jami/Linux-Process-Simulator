// Name: Yasir Jami (3077942)
// CMPT360 Lab 9

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <getopt.h>
#include "findme.h"

/*
 
opendir(const char *) - opens a directory and returns an object of type DIR

readdir(DIR *) - reads the content of a directory and returns an object of type dirent (struct)

closedir(DIR *) - closes a directory

*/

//https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html	
void parseCommands(int argc, char* argv[], char** type, char** name, char** user, int* maxdepth){
	int c;	
	int option_index = 0;
	int optind = 0; // Start optind at 0
	static struct option long_options[] = 
		{
			{"type", required_argument, NULL, 't'},
			{"name", required_argument, NULL, 'n'},
			{"user", required_argument, NULL, 'u'},
			{"maxdepth", required_argument, NULL, 'm'},
			{NULL, 0, NULL, 0}
		};

	while ((c = getopt_long_only(argc, argv, "t:n:u:m:", long_options, &option_index)) !=-1){
		switch(c){
			// -type
			case 't':	
				*type = optarg;
			       /*	
				if (*type != 'f' || *type != 'd' || *type != 's' || *type != 'c' || *type != 'b'){
					printf("No file type for option -type \"%s\"", optarg);
					exit(EXIT_FAILURE);
				}	
				*/
				break;
			// name
			case 'n':
				*name = optarg;
				break;
			// user
			case 'u':	
				*user = optarg;
				break;
			// maxdepth
			case 'm':
				*maxdepth = (int) *optarg - '0';
				break;
		}
		optind++;
	}

	/*	
	if (optind < argc) {
               	printf("non-option ARGV-elements: ");
               	while (optind < argc){
              		printf("%s ", argv[optind++]);
		}
              	printf("\n");	
          }
	*/
}

// Checks --type argument and returns an int
int getFileArgType(char c){
	switch(c){
		// Regular Files
		case 'f':
			return 0;
		// Directory
		case 'd':
			return 1;
		// Symbolic Link
		case 's':
			return 2;
		// Character Device
		case 'c':
			return 3;
		// Block Device
		case 'b':
			return 4;
		// Either invalid file type, or not one of the file types above 
		// (other types like pipe and socket are not accounted for)
		// OR no type argument
		default:
			return -1;
	}
}

// Get file's type
int getFileType(char* file){
        struct stat file_stat;
        stat(file, &file_stat);

        // Regular file
        if (S_ISREG(file_stat.st_mode)){
                return 0;
        }
        // Directory
        else if (S_ISDIR(file_stat.st_mode)){ 
                return 1;
        }
        // Symbolic link
        else if (S_ISLNK(file_stat.st_mode)){
                return 2;
        }
        // Block device 
        else if (S_ISBLK(file_stat.st_mode)){
                return 3;
        }
	// Character device 
        else if (S_ISCHR(file_stat.st_mode)){
                return 4;
        }
        return -1;
}

void dirprint(char* pathname, char* type, int depth, char* name){
	if (depth == 0) {
		return;
	}
	struct stat buf;
	DIR *dir;
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
		stat(fileloc, &buf);
		if (getFileType(fileloc)==1) {
			dirprint(fileloc, type, depth-1, name);
		}
		// Critical section here, each thread will handle printing a directory's contents
		if ((getFileType(fileloc) == argtype) || argtype == -1){ // && file->d_name == name) {
			printf("%s\n", fileloc);
		}

	}
	closedir(dir);
}


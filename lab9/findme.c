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
	int count = 0;

	while (1){
	        int option_index = 0;
		static struct option long_options[] = 
		{
			{"type", required_argument, NULL, 'n'},
			{"name", required_argument, NULL, 't'},
			{"user", required_argument, NULL, 'u'},
			{"maxdepth", required_argument, NULL, 'm'},
			{0, 0, 0, 0}
		};
		// 
		c = getopt_long(argc, argv, "t:n:u:m:", long_options, &option_index);
		if (c == -1){
			//printf("End count: %d\n", count);
			break;
		}
		count++;

		printf("Current opt value: %c\n", (char) c);
		// Do error checking
		switch(c){
			// -type
			case 't':
				printf("File type: %s\n", optarg);
				*type = optarg; 
				/*
				if (type != 'f' || type != 'd' || type != 's' || type != 'c' || type != 'b'){
					printf("No file type for option -type \"%s\"", optarg);
					exit(EXIT_FAILURE);
				}
				*/
				break;
			// name
			case 'n':
				printf("File to look for: %s\n", optarg);
				*name = optarg;
				break;
			// user
			case 'u':
				printf("Owner of file: %s\n", optarg);
				*user = optarg;
				break;
			// maxdepth
			case 'm':
				printf("Look %s directories deep\n", optarg);
				*maxdepth = (int) *optarg - '0';
				break;
		}
	
		if (optind < argc) {
               		printf("non-option ARGV-elements: ");
               		while (optind < argc)
                   		printf("%s ", argv[optind++]);
               		printf("\n");
          	}
	
	}

}
// Checks -file filetype given a valid argument
int getFileType(char c){
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
		default:
			return -1;
	}
}


int fileSystemTests(char* file){
       	struct stat file_stat;
	stat(file, &file_stat);

	// Regular file
	if (S_ISREG(file_stat.st_mode)){
		return 0;
	}
	// Directory
	else if (S_ISDIR(file_stat.st_mode)){
		printf("Directory.\n");
		return 1;
	}
	// Special character
	else if (S_ISCHR(file_stat.st_mode)){
		printf("Character Special.\n");
		return 2;
	}
	// Special block
	else if (S_ISBLK(file_stat.st_mode)){
		printf("Block Special.\n");
		return 3;
	}
	// Pipe or FIFO special file
	else if (S_ISFIFO(file_stat.st_mode)){
		printf("Pipe or FIFO special file.\n");
		return 4;
	}
	// Symbolic link
	else if (S_ISLNK(file_stat.st_mode)){
		printf("Symbolic Link.\n");
		return 5;
	}
	// Socket
	else if (S_ISSOCK(file_stat.st_mode)){
		printf("Socket.\n");
		return 6;
	}
	// Realistically should never reach this point	
	printf("Unknown file.\n");
	return -1;
}


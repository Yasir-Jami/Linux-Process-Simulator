// Name: Yasir Jami & Cole Doris 
// CMPT360 Lab 9

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <getopt.h>
#include <pwd.h>
#include <dirent.h>
#include <pthread.h>
#include <glob.h>
#include "findme.h"

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
			// type
			case 't':	
				*type = optarg;
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
				*maxdepth = atoi(optarg);	
				break;
		}
		optind++;
	}
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

// Get file's type given a string
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

// Function passed to a pthread to perform; prints contents of a directory
void* printDirectories(void* args){
	struct dirargs* d = (struct dirargs*) args; // Struct holding CLI argument variables
	if (d->depth == 0) {
		return NULL;
	}
	char fileloc[500];
	// CLI Variables
	char* pathname = d->pathname;
	char* type = d->type;
	char* name = d->name;
	char* user = d->user;
	int depth = d->depth;
	// Stat and pwd
	struct stat buf;
	struct passwd *p;
	// Dirent
	DIR *dir = opendir(pathname);
	// Check if file is able to be looked through
	if (NULL == dir){
		fprintf(stderr, "Unable to open %s\n", pathname);
		return NULL;
	}
	struct dirent *file;
	// Checks 
	int argtype = getFileArgType(*type);
	int namecheck = checkName(name);
	int usercheck = checkUser(user);
	// Glob - put glob call, size variable,  and size loop up here after
	//if (namecheck == 1){
		glob_t globbuf;
		globbuf.gl_offs = 0;
	//}	
	
	while((file = readdir(dir))) {
		if ((strcmp(file->d_name,".") == 0) || (strcmp(file->d_name, "..") == 0)) {
			continue;
		}
		strcpy(fileloc, pathname);
		strncat(fileloc,"/",2);
		strncat(fileloc, file->d_name, 100);
		stat(fileloc, &buf);
	
		if (getFileType(fileloc)==1){ 
			--(d->depth);
			d->pathname = fileloc;
			printDirectories(args);
		}

		// Check if file's type matches -type argument 
		if (((getFileType(fileloc) == argtype) || argtype == -1)){
			// Check if name option was specified
			if (namecheck == 1){ 
				int glob_flag = 0; // 0 - File did not match glob, 1 - File matched glob
				int size = 0; // Size of list of matched filenames 
				int i = 0;

				// Get list of filenames that matched glob
				glob(name, GLOB_DOOFFS, NULL, &globbuf);
				while (globbuf.gl_pathv[size] != NULL){
					size++;
				}
				//printf("Current glob: %s\n", name);
	
				// Check against all file names that matched the glob
				while (globbuf.gl_pathv[i]){
					// Do not print if file's name does not match -name arg
					//printf("Current filename: %s\n", globbuf.gl_pathv[i]);
					if (strcmp(file->d_name, globbuf.gl_pathv[i]) == 0){
						glob_flag = 1;
						break;
					}
					i++;
				}
				// Go to next file if it does not match glob
				if (glob_flag == 0){continue;}
			}
			// Check if user option was specified
			if (usercheck == 1){
				// Get uid of the file's owner and compare to -user arg
				p = getpwuid(buf.st_uid);	
				if (strcmp(user, p->pw_name) != 0){
					continue;
				}
			}

			if (d->ind == depth){
				printf("%s\n", fileloc);
			}
		}
	}
	closedir(dir);

        return NULL;
}

void dirprint(char* pathname, char* type, char* name, char* user, int depth){
	int nprocs = get_nprocs(); // Number of processes
	struct dirargs args[nprocs];// = malloc(sizeof(struct dirargs)); // Struct containing CLI arguments
        pthread_t tid[nprocs]; // Thread IDs

	// Check if directory exists first
	DIR *dir = opendir(pathname);
	dir = opendir(pathname);
	if (dir == NULL) {
		printf("Not a valid dir. Closing program.\n");
		exit(EXIT_FAILURE);
	}
	closedir(dir);

	/*
	if (strcmp(name, "0") != 0){
		char* glob;
		strcpy(glob, "./");
		strcat(glob, name);
		name = glob; // Of the pattern .*[nameglob]
	}
	*/

	// Thread creation
	for (int i = 0; i < nprocs; i++){
		args[i].pathname = pathname;
		args[i].type = type;
		args[i].name = name;
		args[i].user = user;
		args[i].depth = depth;
		args[i].ind = depth-i; // start at top
                pthread_create(&tid[i], NULL, printDirectories, &args[i]);
                pthread_join(tid[i], NULL);
        }

	// After measuring using time.h, waiting after all threads are created is slower on average
	// Also prints randomly
	/*
	for (int i = 0; i < nprocs; i++){
		pthread_join(tid[i], NULL);
	}
	*/
}

// Checks if name argument was specified
int checkName(char* name){
	if (strcmp(name, "0") == 0 || strcmp(name, "") == 0) return 0;
	else {return 1;}
	
	return 0;
}

// Checks if user argument was specified
int checkUser(char* user){
	if (strcmp(user, "0") == 0 || strcmp(user, "") == 0) return 0;
	else {return 1;}
	
	return 0;
}

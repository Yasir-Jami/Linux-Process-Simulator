// Name: Yasir Jami & Cole Doris
// CMPT360 Lab 9 

#ifndef FINDME_H
#define FINDME_H

// Note: We will not need to store the paths when we find them, just print them

struct dirargs{
        char* pathname; 
	char* type; 
	char* name; 
	char* user; 
	int depth;
	int ind;
};

/*
 * Parses the arguments found in the command line and changes the values accordingly
 * Defaults to ./findme . -type f -name file.c -maxdepth 1
 * type: file type (f: regular file, d: directory, etc.)
 * name: name of file
 * user: owner of the file
 * maxdepth: levels of directories to search through
 */
void parseCommands(int argc, char* argv[], char** type, char** name, char** user, int* maxdepth);

/*
 * Takes a character as input and finds a file type to look for and returns it as an integer
 // 0 - Regular file 
 // 1 - Directory
 // 2 - Symbolic Link
 // 3 - Block Device
 // 4 - Character Device
 */
int getFileArgType(char c);

/* Determines file type given a string. */
int getFileType(char* file);

/*
Uses pthreads to recursively search through directories starting from pathname and prints all files of a specified type

Type can be:
 // -1 - No specified type (look for all files)
 // 0 - Regular file 
 // 1 - Directory
 // 2 - Symbolic Link
 // 3 - Block Device
 // 4 - Character Device
*/
void dirprint(char* pathname, char* type, char* name, char* user, int depth);

// Function passed to thread to perform actual printing of directory contents
void* printDirectories(void* arg);

/* Checks if name argument was specified in command line.
 */
int checkName(char* name);

/* Checks if user argument was specified in command line.
 */
int checkUser(char* user);

#endif

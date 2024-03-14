// Name: Yasir Jami (3077942)
// CMPT360 Lab 3 

#include <stdio.h>
#include <stdlib.h>
#include "fileType.h"

// Perform three tests using a provided file path and determine the file's type or format

int main(int argc, char* argv[]){	
	if (argc != 2){
		printf("Usage: %s [file]\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	FILE* fp = NULL;
	char* filename = argv[1]; // Path to file
	int filetype; // File type - regular file, directory, symlink, etc.
	int elf_or_executable; // Used to determine ELF or executable file
	int ascii_or_binary; // Used to determine file format
	
	// Preliminary check to see if file exists
	if ((fp = fopen(filename, "r")) == NULL){
		printf("Cannot open file.\n");
		exit(EXIT_FAILURE);
	}

	// If it is anything but a regular file, print and return 		
	if ((filetype = fileSystemTests(filename)) != 0){
		return 0;
	}

	else {		// Check if elf or executable - if it is, print message and return	
		if ((elf_or_executable = magicNumberTests(filename)) != -1){
			printMessage(elf_or_executable, -1);	
			return 0;
		}

		// Finally, check if the file is ascii or binary
		ascii_or_binary = asciiOrBinary(filename); // Check if ascii or binary
		printMessage(-1, ascii_or_binary);	
	}
	return 0;
}

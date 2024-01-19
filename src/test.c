#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "dStruct.h"

int main(void){	
	FILE* fp;
	char* dirname = "../newProc"; // Hard-coded
	DIR *processDir; // Directory pointer, used for newProc.
	struct dirent *file; // Current file being examined
	int file_count = 0; // Amount of files in newProc
	char file_contents[50];
	int niceness; // Current process' niceness
	double proctime; // Current process' proctime
	char fileloc[50];
	char* token; // Used for retrieving niceness and proctime

	/* Open newProc directory and check for presence of files*/
	processDir = opendir(dirname);

	if (processDir == NULL){
		printf("No processes available. Closing program.\n");
		return 1;
	}	

	// Read files from the new process directory. Add processes to ready queue one by one
	while ( (file = readdir(processDir)) ){
		if ((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name, "..") == 0)){
			continue;
		}
		file_count++; // Used for pid
		strcpy(fileloc, dirname);
		strncat(fileloc, "/", 2);
		strncat(fileloc, file->d_name, 30);	
		
		// Open file for reading and retrieve niceness and proctime
		fp = fopen(fileloc, "r");	
		if (fp == NULL){
			printf("Couldn't open file.");
		}

		while (fgets(file_contents, 50, fp)){
		}

		printf("Trial %d\n", file_count);		
		printf("Current file contents: %s", file_contents);
		
		// Get first token (which is niceness)
		token = strtok(file_contents, " ");
		niceness = atoi(token);

		/*
		while (token != NULL){
			printf("Current token: %s\n", token);
			token = strtok(NULL, " ");
		}
		*/

		token = strtok(NULL, " ");
		proctime = atof(token);

		printf("Niceness: %d\n", niceness);
		printf("proctime: %f\n\n", proctime); // Need to print a double %f

		}

	return 0;
}

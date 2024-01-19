#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dStruct.h"
#include <dirent.h>

// https://c-for-dummies.com/blog/?p=3246 | Using dirent

int main(void){
	// Queues
	struct node* ready_queue = NULL; // Queue for processes ready to run
	struct node* running_queue = NULL; // Queue for processes that are running
	// Timing
	double initial_time = 0.0; // Set cputime to 0 initially
	double delta = 0.1; // Increment time. Add to cputime for each entry as well
	// File handling
	DIR *processDir; // Directory pointer, used for newProc.
	struct dirent *file; // Current file being examined
	int file_count = 0; // Amount of files in newProc

	/* Open newProc directory and check for presence of files*/
	processDir = opendir("../newProc");

	if (processDir == NULL){
		puts("No processes available. Closing program.");
		return 1;
	}
	
	while ( (file = readdir(processDir)) ){
		if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0){
			continue;
		}
		file_count++;
		printf("File %3d: %s\n", file_count, file->d_name);
	}
	
	closedir(processDir);
	return 0;
}

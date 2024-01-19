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
	double time_delta = 0.1; // Increment time. Add to cputime for each entry as well
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

		// Add file niceness and proctime to process	
		// process, pid, status, niceness, cputime, proctime
		// pid --> increment based on current file number
		// status - based on ***?
		// niceness - readin from file
		// proctime - readin from file
		printf("Adding %s to ready queue...\n", file->d_name);
		ready_queue = push(struct node *process, file_count, 1, process->niceness, initial_time, process->proctime);
		/*
		if (ready_queue == NULL || getSize(ready_queue) < file_count){
			// Add process from file using the their niceness and status
			printf("Adding %s to ready queue...\n", file->d_name);
		}
		*/
	
		//ready_queue = struct node file; 
		//running_process = file;

		// Add node using info from given file
		//ready_queue = push();
		
		printf("Adding %s to running queue \n", file->d_name);
		// Simulating process running
		while (cputime != proctime || cputime < proctime){
			cputime+=time_delta;
		}
		printf("%s finished at %f\n", file->d_name, process->cputime);
	}	
	closedir(processDir);

	return 0;
}

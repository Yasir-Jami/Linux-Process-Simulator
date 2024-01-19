#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "dStruct.h"

// https://c-for-dummies.com/blog/?p=3246 | Using dirent

// Status Codes:
// 0: Terminated
// 1: Ready
// 2: Running

int main(void){
	// Queues
	struct node* ready_queue = NULL; // Queue for processes ready to run
	struct node* running_queue = NULL; // Queue for processes that are running
	// Timing
	double initial_time = 0.0; // Set cputime to 0 initially
	double time_delta = 0.1; // Increment time. Add to cputime for each entry as well
	// File handling
	FILE* fp;
	int file_count = 0; // Number of files in newProc
	char file_contents[50]; // To store read file contents
	char fileloc[50]; // Where file pointer will point to
        char* token; // Used for retrieving niceness and proctime
	char* dirname = "../newProc"; // Hard-coded
	DIR *processDir; // Directory pointer, used for newProc.
	struct dirent *file; // Current file being examined
	// Process Variables
	int niceness; // Current process' niceness
	double proctime; // Current process' proctime

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

                // Point to file
                fp = fopen(fileloc, "r");
                if (fp == NULL){
                        printf("Couldn't open file.");
                }
		// Read file
                while (fgets(file_contents, 50, fp)){
                }

                // Get niceness
                token = strtok(file_contents, " ");
                niceness = atoi(token);
		// Get proctime
                token = strtok(NULL, " ");
                proctime = atof(token);
                	
		// Create and push node 

		// Add file niceness and proctime to process	
		// process, pid, status, niceness, cputime, proctime
		// pid --> increment based on current file number
		// status - based on ***?
		// niceness - readin from file
		// proctime - readin from file
		printf("Adding %s to ready queue...\n", file->d_name);
		ready_queue = push(struct node *process, file_count, 1, niceness, initial_time, proctime);
		}
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

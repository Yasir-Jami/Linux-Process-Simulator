#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "dStruct.h"
#include "procLib.h"

struct node* admit(struct node* ready_queue)
{
	// File handling
	FILE* fp;
	int file_count = 0; // Number of files in newProc - used to determine pid
	char file_contents[50]; // To store read file contents
	char fileloc[50]; // Location of current file in the directory structure
        char* token; // Used for retrieving niceness and proctime from file
	char* dirname = "../newProc"; // Hard-coded
	DIR *processDir; // Will point to newProc
	struct dirent *file; // Current file being examined
	// Process Variables
	int niceness; // Current process' niceness
	double proctime; // Current process' proctime

	/* Open newProc directory and check for presence of files*/
	processDir = opendir(dirname);
	if (processDir == NULL){
		printf("No new processes available. Closing program.\n");
		exit(EXIT_FAILURE);	
	}
	
	// Read from files in the new process directory. Add processes to ready queue one by one
	while ( (file = readdir(processDir)) ){
		if ((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name, "..") == 0)){
			continue;
		} 
		// File location in the form ../newProc/(FILE)
		strcpy(fileloc, dirname);
	        strncat(fileloc, "/", 2);
		strncat(fileloc, file->d_name, 30);
                // Point to file - goes to next process if file can't be opened
                fp = fopen(fileloc, "r");
                if (fp == NULL){
                        printf("Could not open file.\n");
			continue;
                }
		// Read file and put into file_contents
                while (fgets(file_contents, 50, fp)){
                }

                // Get niceness
                token = strtok(file_contents, ",");
                niceness = atoi(token);
		// Get proctime
                token = strtok(NULL, ",");
                proctime = atof(token);

		// After reading from file, make a new process and add to ready queue
		printf("Adding process %s to ready queue with PID %d...\n", file->d_name, file_count);
		ready_queue = push(ready_queue, file_count, 1, niceness, 0.0, proctime);
		file_count++; // Used for pid
	}
	closedir(processDir);
	return ready_queue;
}

struct node* dispatch(struct node* ready_queue, struct node* running_queue, int pid){
	struct node* process = getEntry(ready_queue, pid);
	running_queue = push(running_queue, pid, 2, process->niceness, process->cputime, process->proctime);
	ready_queue = pop(process);
	return running_queue;
}

struct node* processExit(struct node* running_queue){
	running_queue->status = 3;
	struct node* remove = pop(running_queue); // Need to fix pop so that it is a void func	
	return running_queue;
}

void addLogEntry(struct node* process, int time){
	FILE *fp = NULL;
	if (process->pid == 0){
		fp = fopen("../log/logfile", "w");
		fprintf(fp, "%d, %d, %d, %d, %f, %f\n", time, process->pid, 3, process->niceness, process->cputime, process->proctime);
	}
	else{
		fp = fopen("../log/logfile" , "a");
		fprintf(fp, "%d, %d, %d, %d, %f, %f\n", time, process->pid, 3, process->niceness, process->cputime, process->proctime);
	}
	fclose(fp);
}

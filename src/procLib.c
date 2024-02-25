#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
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
		printf("Adding process %s to ready queue %d with PID %d...\n", file->d_name, niceness, file_count);
		ready_queue = push(ready_queue, file_count, 1, niceness, 0.0, proctime);
		file_count++;
	}
	closedir(processDir);
	return ready_queue;
}

// Round Robin: rotate out currently running process and push it to ready queue
void rotate(struct node** ready_queue, struct node** running_queue){
	struct node* process = pop(running_queue);
	append(ready_queue, process);
}

void addLogEntry(struct node* ready_queue, struct node* running_queue, int time){
	FILE *fp = NULL;
	char fname[50] = "";
	char pathname[] = "../log/logfile";
	char date[16]  = __DATE__;
	char algorithm[12] = ALGOR;
	int i = 0;

	while (date[i] != '\0'){		
		if (date[i] == ' '){
			date[i] = '-';
		}
		i++;
	}	
	sprintf(fname, "%s-%s-%s", pathname, date, algorithm); // Form full logfile name
	
	// Append log entry to logfile
	fp = fopen(fname, "a");
	// Ready Queue
	while (ready_queue != NULL){
		fprintf(fp, "%d, %d, %d, %d, %f, %f\n", current_time, ready_queue->pid, ready_queue->status, 
				ready_queue->niceness, ready_queue->cputime, ready_queue->proctime);
		ready_queue = ready_queue->next;
	}
	// Running Queue - loop used in case we have multiple processes later 
	while (running_queue != NULL){
	fprintf(fp, "%d, %d, %d, %d, %f, %f\n", current_time, running_queue->pid, running_queue->status, 
			running_queue->niceness, running_queue->cputime, running_queue->proctime);
			running_queue = running_queue->next;
	}	
	fclose(fp);
}

// Pop according to the scheduling algorithm used
struct node* popFromReadyQueue(struct node** ready_queue, char* algorithm){
	// SJF - Get PID of the process with the lowest proctime
	if (strcmp(algorithm, "ALGOR_SJF") == 0){
		struct node* temp = *ready_queue;
		while (temp != NULL){
			if (temp->proctime < lowest_time){
				pid = temp->pid;
			}
			temp = temp->next;
		}
		struct node* process = popAtPid(ready_queue, pid);
	}
	// FIFO - Pop the first process added
	else if (strcmp(algorithm, "ALGOR_FIFO")){struct node* process = popAtEnd(ready_queue);}
	// RR and MLFQ - Pop normally
	else{struct node* process = pop(ready_queue);}

	return process;
}

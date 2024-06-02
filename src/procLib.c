// Authors: Yasir Jami & Cole Doris 

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
		printf("Adding process %s to ready queue with PID %d...\n", file->d_name, file_count);	
		ready_queue = push(ready_queue, file_count, 1, niceness, 0.0, proctime, niceness);
		file_count++;
	}
	closedir(processDir);
	return ready_queue;
}

// Round Robin: rotate out currently running process and push it to ready queue
void rotate(struct node** ready_queue, struct node** running_queue){
	struct node* process = pop(running_queue);
	process->status = 1;
	append(ready_queue, &process);
}

void addLogEntry(struct node** queue_array, struct node* running_queue, double current_time, char* filename, int size){
	FILE *fp = NULL;
	char* algorithm = xstr(ALGOR);
	int i = 0;
	struct node* temp = NULL;

	// Append log entry to logfile
	fp = fopen(filename, "a");

	// Ready Queue	
	while (i < size){
		temp = queue_array[i];
		while (temp != NULL){	
			fprintf(fp, "%f, %d, %d, %d, %f, %f\n", current_time, temp->pid, temp->status, 
					temp->niceness, temp->cputime, temp->proctime);		
			temp = temp->next;
		}
		i++;
	}

	if (strcmp(algorithm, "ALGOR_MLFQ") != 0 && running_queue){
		// Running Queue
		fprintf(fp, "%f, %d, %d, %d, %f, %f\n", current_time, running_queue->pid, running_queue->status, 
				running_queue->niceness, running_queue->cputime, running_queue->proctime);
	}

	fclose(fp);
}

// Pop according to the scheduling algorithm used
struct node* popFromReadyQueue(struct node** ready_queue, char* algorithm){
	// SJF - Get PID of the process with the lowest proctime
	if (strcmp(algorithm, "ALGOR_SJF") == 0){
		struct node* temp = *ready_queue;
		double lowest_time = 500.0;
		int pid = 0;
		while (temp != NULL){
			if (temp->proctime < lowest_time){
				pid = temp->pid;
				lowest_time = temp->proctime;
			}
			temp = temp->next;
		}
		return popAtPid(ready_queue, pid);
	}
	// FIFO - Pop the first process added
	else if (strcmp(algorithm, "ALGOR_FIFO") == 0){
		return popAtEnd(ready_queue);
	}
	// RR and MLFQ - Pop normally
	return pop(ready_queue);
}

int check_queues(struct node** queue_array, int size){
	int i = 0;
	int priority = size;

	while (queue_array[i] == NULL){
		priority--;
		i++;
	}
	return priority;
}

void reset_queues(struct node** queue_array){	
	struct node* current_queue = NULL; 
	struct node* process = NULL;
	
	// Check the original niceness of all processes and place them back in their original queue 
	for (int i = 0; i < 5; i++){
		current_queue = queue_array[i];
		while (current_queue != NULL){
			if (current_queue->niceness != current_queue->original_niceness){
				process = pop(&current_queue);
				queue_array[5 - process->original_niceness] = push(queue_array[5 - process->original_niceness], process->pid, process->status, 
						process->original_niceness, process->cputime, process->proctime, process->original_niceness);
				free(process);
				process = NULL;
			}
			current_queue = current_queue->next;
		}
	}
}

void addToQueueArray(struct node** ready_queue, struct node** niceness5_queue, struct node** niceness4_queue, 
		struct node** niceness3_queue, struct node** niceness2_queue, struct node** niceness1_queue){
	int i = 0;
	struct node* process = NULL;
	while (ready_queue != NULL){	
		switch(ready_queue->niceness){
			case 1: process = pop(&ready_queue);
					niceness1_queue = push(niceness1_queue, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness); 
					break;
            case 2: process = pop(&ready_queue);
					niceness2_queue = push(niceness2_queue, process->pid, process->status,
							process->niceness, process->cputime, process->proctime, process->niceness);
					break;
            case 3: process = pop(&ready_queue);
					niceness3_queue = push(niceness3_queue, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness); 
				       	break;
            case 4:	process = pop(&ready_queue);
					niceness4_queue = push(niceness4_queue, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness);
					break;
			case 5: process = pop(&ready_queue);
					niceness5_queue = push(niceness5_queue, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness);
					break;
			default: process = pop(&ready_queue); 
					niceness5_queue = push(niceness5_queue, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness);
					break;
			}
        }
}

// Switch to queue array instead of bringing every queue, more efficient
struct node* lowerProcessPriority(struct node** running_queue, struct node** niceness5_queue, struct node** niceness4_queue, 
				struct node** niceness3_queue, struct node** niceness2_queue, struct node** niceness1_queue, int priority){
		switch(priority){
				case 5: setNiceness(running_queue, running_queue->pid, priority);
					temp = pop(&running_queue);
					append(&niceness4_queue, &temp);
					break;
				case 4: setNiceness(running_queue, running_queue->pid, priority);
					temp = pop(&running_queue);
					append(&niceness3_queue, &temp);
					break;
				case 3: setNiceness(running_queue, running_queue->pid, priority);
					temp = pop(&running_queue);
					append(&niceness2_queue, &temp);
					break;
				
				case 2: setNiceness(running_queue, running_queue->pid, priority);
					temp = pop(&running_queue);
					append(&niceness1_queue, &temp);
					break;

				case 1: setNiceness(running_queue, running_queue->pid, 1);
					temp = pop(&running_queue);
					append(&niceness1_queue, &temp);
					break;
				default:
					setNiceness(running_queue, running_queue->pid, 1);
					temp = pop(&running_queue);
					append(&niceness1_queue, &temp);
					break;
				}	
}

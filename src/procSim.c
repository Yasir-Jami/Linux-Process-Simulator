/*
Name: Yasir Jami & Cole Doris
360 Lab 6 (Group 4)
*/
// Pre-processor directives will be defined in procLib.h, so they can be used in procLib.c and procSim.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "dStruct.h"
#include "procLib.h"

// Queue Status Codes:
// 1: Ready
// 2: Running
// 3: Complete

int main(int argc, char* argv[]){
	// Queues
	struct node* ready_queue = NULL; // Holds processes ready to run
	struct node* running_queue = NULL; // Holds processes that are running
	struct node* temp = NULL; // Temporarily holds processes
	int exit_flag = 1; // Determines process loop state
	// 4 niceness queues for MLFQ
	int priority = 5; // Determines priority queue to run
	int array_size = 0; // Determines queue array size
	struct node* niceness5_queue = NULL;
	struct node* niceness4_queue = NULL;
        struct node* niceness3_queue = NULL;
        struct node* niceness2_queue = NULL;
        struct node* niceness1_queue = NULL;
	// Timing
	double timer = 0.0; // Global timer
	double time_dt = TIME_DT; // Time increment
	double time_qt = TIME_JIFFY; // Time slice - max allowed time for a process to run before swapping - essentially equal to proctime for SJF and FIFO
	double time_reset = TIME_RESET; // When exceeded, resets all processes back to their original queues
	double elapsed = 0.0; // Tracks how long a process has been running for RR and MLFQ
	double reset_timer = 0.0; // Tracks how long processes have been running for MLFQ 

	// For use in the script 
	char algorithm[24] = xstr(ALGOR); // Scheduling Algorithm - macro found in procLib.h
	if (argc > 1) {
                if (!strcmp(argv[1], "0")) {
                        strcpy(algorithm, "ALGOR_FIFO");
                } else if (!strcmp(argv[1], "1")) {
                        strcpy(algorithm, "ALGOR_SJF");
                } else if (!strcmp(argv[1], "2")) {
                        strcpy(algorithm, "ALGOR_RR");
                } else if (!strcmp(argv[1], "3")) {
                        strcpy(algorithm, "ALGOR_MLFQ");
        	}
	}
	
	// Create logfile
	FILE* fp = NULL;
	char filename[100] = "";
	char pathname[] = "../log/logfile";
	char date[16]  = __DATE__;
	int i = 0;
	while (date[i] != '\0'){
		if (date[i] == ' '){
			date[i] = '-';
		}
		i++;
	}
	sprintf(filename, "%s-%s-%s", pathname, date, algorithm);
	char* name = filename + strlen(pathname)+1; // Without pathname
	printf("Using %s\n", algorithm);
	printf("Storing in %s\n\n", name);
	fp = fopen(filename, "w"); // Will truncate logfile of the same name to 0 if one is present
	fclose(fp);

	// Determine array size
	if (strcmp(algorithm, "ALGOR_MLFQ") == 0){
		array_size = 5;	
	} 
	else {
		array_size = 1;	
	}
		
	struct node* queue_array[array_size];

	// Add all processes to ready queue
	ready_queue = admit(ready_queue);
	// Increment time by (time_delta * # of processes)
	printf("\n");

	// Add processes to queues according to their niceness
	if (strcmp(algorithm, "ALGOR_MLFQ") == 0){
                int i = 0; // Used for loops related to MLFQ	
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
       		queue_array[0] = niceness5_queue;
		queue_array[1] = niceness4_queue;
		queue_array[2] = niceness3_queue;
		queue_array[3] = niceness2_queue;
		queue_array[4] = niceness1_queue; 
	
		// Start at first non-empty queue
		i = 0;
		while (i < 5){
			if ((running_queue = queue_array[i]) != NULL){
				break;
			}
			i++;
		}
	}
	
	else {
		queue_array[0] = ready_queue;
	}		

	int size = sizeof(queue_array)/sizeof(ready_queue); // Size of a process/struct pointer
	addLogEntry(queue_array, running_queue, timer, filename, size);

	// Add processes to running queue while there are still processes in queues
	while (exit_flag){
		// Add process to running queue according to algorithm used	
		if (strcmp(algorithm, "ALGOR_MLFQ") == 0){
			priority = check_queues(queue_array, size);
			running_queue = queue_array[5 - priority];
			i++;
		}
		else {
			running_queue = popFromReadyQueue(&queue_array[0], algorithm);
		}

		running_queue->status = 2;
		printf("Running process with PID %d...\n", running_queue->pid);
		timer+=time_dt;	
		addLogEntry(queue_array, running_queue, timer, filename, size);
		elapsed = 0.1;

		// Main Process Loop - stop when the process's cputime meets or exceeds proctime	
		while (getCpuTime(running_queue, running_queue->pid) <= running_queue->proctime){
			// Increment global time and add a new log entry for every process in both queues
			timer+=time_dt;
			running_queue->cputime+=time_dt;
			addLogEntry(queue_array, running_queue, timer, filename, size);

			if ((strcmp(algorithm, "ALGOR_MLFQ") == 0)){
				// Increment timers
				elapsed+=time_dt;
				reset_timer+=time_dt;	
				// Check if it's time to reset queues
				if (reset_timer > time_reset){
					running_queue->status = 1;
					reset_queues(queue_array); // Return all processes to their original queues
					priority = check_queues(queue_array, size);
					running_queue = queue_array[5 - priority]; // Start back at highest niceness queue
					reset_timer = 0.1;
					elapsed = 0.1; 
				}
			
				// Move process to lower priority queue
				if (elapsed > time_qt){	
					running_queue->status = 1;
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
					if (running_queue == NULL){
						temp = pop(&queue_array[5 - priority]);
						priority = check_queues(queue_array, size);
						running_queue = queue_array[priority];
						running_queue->status = 2;
					}
					else{
						running_queue->status = 2;
					}
					elapsed = 0.1;
				}
			}

			// For Round Robin, check if global time has elapsed a jiffy
			if ((strcmp(algorithm, "ALGOR_RR") == 0) && queue_array[0]){
				elapsed+=time_dt;
				// Rotate process back into ready queue, add next process to running
				if (elapsed > time_qt){
					rotate(&queue_array[0], &running_queue); // Rotate current process into ready queue	
					running_queue = pop(&queue_array[0]);
					elapsed = 0.1;
				}
			}
		}
		// Note that process has finished and make a log entry
		running_queue->status = 3;
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);
		addLogEntry(queue_array, running_queue, timer, filename, size);
	
		// When all queues are empty, exit simulator
		if (strcmp(algorithm, "ALGOR_MLFQ") == 0){	
			if (!(queue_array[0] && queue_array[1] && queue_array[2] && queue_array[3] && queue_array[4])){
				exit_flag = 0;
			}
		}
		else if (queue_array[0] == NULL){
			exit_flag = 0;
		}

		temp = pop(&running_queue);
		free(temp);
		temp = NULL;

	}	
	printf("Total time taken: %f\n", timer);
	return 0;
}

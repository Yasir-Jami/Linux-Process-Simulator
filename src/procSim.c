/*
Name: Yasir Jami & Cole Doris
360 Lab 5 (Group 4)
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
	struct node* ready_queue = NULL; // Holds processes ready to run - niceness 5 queue for MLFQ 
	struct node* running_queue = NULL; // Holds processes that are running
	struct node* temp = NULL; // Temporarily holds processes
	// 4 niceness queues for MLFQ
	int priority = 5; // Determines priority queue to run
	int array_size = 0; // Determines queue array size
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

	// Add processes according to their niceness
	if (strcmp(algorithm, "ALGOR_MLFQ") == 0){
                int i = 0; // Used for loops related to MLFQ	
		struct node* process = NULL;
                struct node* temp = ready_queue;
                while (temp != NULL){
                        switch(temp->niceness){
                                case 1: process = popAtPid(&ready_queue, ready_queue->pid);
                                        niceness1_queue = push(process, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness);
                                        break;
                                case 2: process = popAtPid(&ready_queue, ready_queue->pid);
                                        niceness2_queue = push(process, process->pid, process->status,
							process->niceness, process->cputime, process->proctime, process->niceness);
                                        break;
                                case 3: process = popAtPid(&ready_queue, ready_queue->pid); 
                                        niceness3_queue = push(process, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness); 
				       	break;
                                case 4: process = popAtPid(&ready_queue, ready_queue->pid);
                                        niceness4_queue = push(process, process->pid, process->status, 
							process->niceness, process->cputime, process->proctime, process->niceness);
                                        break;
                        }
                        temp = temp->next;
                }
       		queue_array[0] = ready_queue;
		queue_array[1] = niceness1_queue;
		queue_array[2] = niceness2_queue;
		queue_array[3] = niceness3_queue;
		queue_array[4] = niceness4_queue;
	
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
	
	int size = sizeof(queue_array)/sizeof(queue_array[0]); // Size of a process/struct pointer
	addLogEntry(queue_array, running_queue, timer, filename, size);

	// Add processes to running queue while there are still processes in queues
	// Maybe set condition "when queue array isn't empty"
	while (ready_queue || niceness1_queue || niceness2_queue || niceness3_queue || niceness4_queue){
		// Add process to running queue according to algorithm used
		if (strcmp(algorithm, "ALGOR_MLFQ") == 0){
			i = 0;
			do {
				running_queue = queue_array[5 - priority + i];
				i++;
			}
			while (running_queue == NULL);
		}
		else {
			queue_array[0] = popFromReadyQueue(&ready_queue, algorithm);
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
				time_reset+=time_dt;
				// Check if it's time to reset queues
				if (time_reset > reset_timer){	
					running_queue->status = 1;
					reset_queues(queue_array); // Return all processes to their original queues
					priority = 5;
					while (queue_array[5 - priority] == NULL){	
							priority--;
					}
					running_queue = queue_array[5 - priority]; // Start back at highest niceness queue
					elapsed = 0.1; 
				}
				// Move process to lower priority queue
				if (elapsed > time_qt){
					switch(priority){
						// Check if we can do append(queueToPopTo, pop(queue)) so temp can be omitted entirely
						case 5: setNiceness(ready_queue, ready_queue->pid, (ready_queue->niceness)-1);
							temp = popAtPid(&ready_queue, ready_queue->pid);
							append(&niceness4_queue, &temp);
							break;
						case 4: setNiceness(niceness4_queue, niceness4_queue->pid, (niceness4_queue->niceness)-1);
							temp = popAtPid(&niceness4_queue, niceness4_queue->pid);
							append(&niceness4_queue, &temp);
							break;
						case 3: setNiceness(niceness3_queue, niceness3_queue->pid, (niceness3_queue->niceness)-1);
							temp = popAtPid(&niceness3_queue, niceness3_queue->pid);
							append(&niceness2_queue, &temp);
							break;
				
						case 2: setNiceness(niceness2_queue, niceness2_queue->pid, (niceness2_queue->niceness)-1);
							temp = popAtPid(&niceness2_queue, niceness2_queue->pid);
							append(&niceness1_queue, &temp);
							break;

						case 1: setNiceness(niceness1_queue, niceness1_queue->pid, (niceness1_queue->niceness)-1);
							temp = popAtPid(&niceness1_queue, niceness1_queue->pid); // Push process to back at lowest queue
							append(&niceness1_queue, &temp);
							break;
					}
					elapsed = 0.1;
					priority = check_queues(queue_array, priority, size); // Check highest queue and change currently running queue accordingly 
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
		
		// No more processes left in queue
		if (running_queue->next == NULL){
			free(running_queue);
			running_queue = NULL;
		}
		else {
			temp = pop(&running_queue);
			free(temp);
			temp = NULL;
		}	
	}
	}
	printf("Total time taken: %f\n", timer);
	return 0;
}

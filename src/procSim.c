#include <stdio.h>
#include "dStruct.h"
#include "procLib.h"
#include <math.h>

// Pre-processor directives will be defined in procLib.h, so it can be used in procLib.c and procSim.c

// Queue Status Codes:
// 1: Ready
// 2: Running
// 3: Complete

int main(void){
	// Queues
	// 5 Queues for Multi-level Feedback Queue - Depends on niceness
	struct node* ready_queue = NULL; // Acts as the niceness 5 queue for MLFQ
	struct node* niceness4_queue = NULL;
	struct node* niceness3_queue = NULL;
	struct node* niceness2_queue = NULL;
	struct node* niceness1_queue = NULL;
	struct node* running_queue = NULL; // Queue for processes that are running
	struct node* temp = NULL; // Used to temporarily hold nodes when removing from running queue
	struct node* process = NULL; // Used to pass processes
	// Timing
	double timer = 0.0; // Global timer	
	double time_dt = TIME_DT; // Time increment
	double time_qt = TIME_JIFFY; // Max allowed time for a process to run before swapping - equal to proctime for SJF and FIFO
	double time_reset = TIME_RESET; // Time at which the MLFQ resets, and all queues are switched to priorities
	char algorithm[24] = ALGOR; // Scheduling Algorithm
	int pid = 0; // Used to determine which processes are added to running queue
	double lowest_time = 500.0; // Used in SJF to determine process with lowest proctime

	printf("Using %s\n", algorithm);

	// First add all processes to ready queue
	ready_queue = admit(ready_queue);
	// Push to queue according to its niceness - any process with a niceness not within 1-4 remains in ready_queue
	if (strcmp(algorithm, "ALGOR_MLFQ") == 0){
		struct node* process = NULL;
		temp = ready_queue;
		while (temp != NULL){
			switch(temp->niceness){
				case 1: process = popAtPID(ready_queue, process->pid);
					niceness1_queue = push(process, process->pid, process-> 
							status, process->niceness, process->cputime, process->proctime);	
					break;
				case 2: process = popAtPID(ready_queue, process->pid);	
					niceness2_queue = push(process, process->pid, process-> 
							status, process->niceness, process->cputime, process->proctime);	
					break;
				case 3: process = popAtPID(ready_queue, process->pid); 
					niceness3_queue = push(process, process->pid, process-> 
							status, process->niceness, process->cputime, process->proctime);	
					break;
				case 4: process = popAtPID(ready_queue, process->pid);
					niceness4_queue = push(process, process->pid, process-> 
							status, process->niceness, process->cputime, process->proctime);
					break;
			}
			temp = temp->next;
		}
	}
	printf("\n");

	// Add processes to running queue while all queues are not equal to null
	while (ready_queue && niceness2_queue && niceness3_queue && niceness4_queue){
		// Add process according to algorithm used, remove process from ready queue

		if (strcmp(algorithm, "ALGOR_MLFQ")){
			printf("Using multi-level queue.");
			process =
			// Look for the highest priority queue that's not empty and use that queue
		}
	
		// Pop based on algorithm
		else{	
		process = popFromReadyQueue(ready_queue, algorithm);
		}

		printf("Dispatching process with PID %d to running queue...\n", process->pid);
		running_queue = dispatch(process, running_queue, pid); 
		timer+=time_delta;
		
		// Main Process Loop - stop when the process's cputime meets or exceeds proctime
		while ((getCpuTime(running_queue, running_queue->pid) != running_queue->proctime) ||
			(getCpuTime(running_queue, running_queue->pid) < running_queue->proctime)){
			
			running_queue->cputime+=time_delta;
			timer+=time_delta;
			
			// Check if loop timer has elapsed a jiffy
			if ((strcmp(algorithm, "ALGOR_RR") == 0) && ((fmod(running_queue->cputime, time_qt)) == 0)){	
				temp = pop(running_queue);
				ready_queue = popToEnd(ready_queue, temp);
				temp = NULL; // Consider freeing if reassigning pointer later does not segfault
			}
		}
		// Note that process has finished and make a log entry
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);
		addLogEntry(running_queue, timer);	
		addLogEntry(removed_node, timer, removed_node->status);
	}
	printf("Total time taken: %f\n", timer);

	// Should be null anyways, test after
	/*
	freeList(ready_queue);
	freeList(temp);
	freeList(running_queue);
	*/

	return 0;
}

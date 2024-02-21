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
	printf("\n");

	// Add processes to running queue while all queues are not equal to null
	while (ready_queue){
		// Add process according to algorithm used, remove process from ready queue
		process = popFromReadyQueue(&ready_queue, algorithm);
		
		printf("Dispatching process with PID %d to running queue...\n", process->pid);
		running_queue = dispatch(&process, &running_queue, pid); 
		timer+=time_delta;
		
		// Main Process Loop - stop when the process's cputime meets or exceeds proctime
		while ((getCpuTime(running_queue, running_queue->pid) != running_queue->proctime) ||
			(getCpuTime(running_queue, running_queue->pid) < running_queue->proctime)){
			
			running_queue->cputime+=time_delta;
			timer+=time_delta;
			
			// Check if loop timer has elapsed a jiffy
			if ((strcmp(algorithm, "ALGOR_RR") == 0) && ((fmod(getCpuTime(running_queue, running_queue->pid), time_qt)) == 0)){
				temp = pop(running_queue);
				ready_queue = append(ready_queue, temp); // Place node at end of ready queue
				break;
			}
		}
		// Note that process has finished and make a log entry
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);	
		addLogEntry(temp, timer, temp->status);
		temp = NULL; 
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

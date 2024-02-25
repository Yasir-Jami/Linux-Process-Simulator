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
	struct node* ready_queue = NULL; // Holds processes ready to run 
	struct node* running_queue = NULL; // Holds processes that are running
	struct node* temp = NULL; // Used to temporarily hold processes when removing from running queue
	struct node* process = NULL; // Used to pass processes to running queue 
	// Timing
	double timer = 0.0; // Global timer	
	double time_dt = TIME_DT; // Time increment
	double time_qt = TIME_JIFFY; // Max allowed time for a process to run before swapping - essentially equal to proctime for SJF and FIFO
	double time_reset = TIME_RESET; // Time at which the MLFQ resets, and all queues are switched to priorities
	char algorithm[24] = ALGOR; // Scheduling Algorithm
	int pid = 0; // Used for logging 
	int cputime = 0; // Used for logging
	double lowest_time = 500.0; // Used in SJF to determine process with lowest proctime

	printf("Using %s\n", algorithm);

	// Add all processes to ready queue
	ready_queue = admit(ready_queue);
	printf("\n");

	// Add processes to running queue while all queues are not equal to null
	while (ready_queue){
		// Add process to running queue according to algorithm used, remove process from ready queue
		running_queue = popFromReadyQueue(&ready_queue, algorithm);
		printf("Dispatching process with PID %d to running queue...\n", running_queue->pid); 
		addLogEntry(ready_queue, running_queue, timer);	
		timer+=time_delta;
		
		// Main Process Loop - stop when the process's cputime meets or exceeds proctime
		while ((getCpuTime(running_queue, running_queue->pid) != running_queue->proctime) ||
			(getCpuTime(running_queue, running_queue->pid) < running_queue->proctime)){
			// Increment global time and add a new log entry for every process in both queues
			timer+=time_delta;
			running_queue->cputime+=time_delta;	
			addLogEntry(ready_queue, running_queue, time);
			
			// Check if global time has elapsed a jiffy
			if ((strcmp(algorithm, "ALGOR_RR") == 0) && ((fmod(getCpuTime(running_queue, running_queue->pid), time_qt)) == 0)){	
				rotate(&ready_queue, &running_queue); // Rotate current process into ready queue
				running_queue = pop(&ready_queue);
				printf("Dispatching process with PID %d to running queue...\n", process->pid);
				addLogEntry(ready_queue, running_queue, timer);
				timer+=time_delta;
			}
		}
		// Note that process has finished and make a log entry
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);
		addLogEntry(ready_queue, running_queue, timer);
		// Check here for bugs - change implementation in case running has multiple processes 
		free(running_queue);
		running_queue = NULL;
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

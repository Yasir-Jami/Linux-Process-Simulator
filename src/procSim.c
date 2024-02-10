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
	struct node* ready_queue = NULL; // Queue for processes ready to run
	struct node* running_queue = NULL; // Queue for processes that are running
	// Timing
	double timer = 0.0; // Global timer	
	double time_dt = TIME_DT; // Time increment
	double time_qt = TIME_JIFFY; // Max allowed time for a process to run before swapping - equal to proctime for SJF and FIFO
	char algorithm[24] = ALGOR; // Scheduling Algorithm
	int pid = 0; // Used to determine which processes are added to running queue
	double lowest_time = 500.0; // Used in SJF to determine process with lowest proctime

	printf("Using %s\n", algorithm);

	// Add all processes in the newProc directory to the ready queue
	ready_queue = admit(ready_queue);
	printf("\n");
	
	// Add processes to running queue while ready queue is not empty
	while (ready_queue){
		// Add process according to algorithm used, remove process from ready queue
		
		// Pop based on algorithm
		struct node* process = popReadyQueue(&ready_queue, algorithm);

		printf("Dispatching process with PID %d to running queue...\n", process->pid);
		running_queue = dispatch(process, running_queue, pid); 
		timer+=time_delta;
	
		// If ALGOR_RR, use an if statement that takes to a new loop or alter current loop to apply if statements with jiffies

		// Process Simulator - stop when cputime meets or exceeds proctime
		while ((getCpuTime(running_queue, running_queue->pid) != running_queue->proctime) ||
			(getCpuTime(running_queue, running_queue->pid) < running_queue->proctime)){
			
			running_queue->cputime+=time_delta;
			timer+=time_delta;
			
			// Check if timer is divisible by time_qt
			if ((strcmp(algorithm, "ALGOR_RR") == 0) && ((fmod(timer, time_qt)) == 0)){
				timer+=time_delta;
				ready_queue = pop(running_queue);
			}

			// Add log entry here, add status parameter
		}
		// Note that process has finished and make a log entry
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);
		addLogEntry(running_queue, timer);
		removed_node = pop(running_queue);
		removed_node->status = 3;
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

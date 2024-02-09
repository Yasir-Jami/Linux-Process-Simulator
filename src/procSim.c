#include <stdio.h>
#include "dStruct.h"
#include "procLib.h"

// Pre-processor directives will be defined in the header, so it can be used in procLib.c and procSim.c

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
	double time_dt = TIME_DT;
	double time_qt = TIME_JIFFY; // Max allowed time for a process to run before swapping - equal to proctime for SJF and FIFO
	char algorithm[24] = ALGOR;
	int pid = 0; // Used to determine which processes are added to running queue
	double lowest_time = 500.0; // Used in SJF to determine process with lowest proctime

	// Add all processes in the newProc directory to the ready queue
	ready_queue = admit(ready_queue);
	struct node* temp = ready_queue;	
	printf("\n");
	
	// Add process
	while (ready_queue){
		// Add process to running queue by PID, remove process from ready queue
		
		// Get PID of the process with the lowest proctime
		if (strcmp(algorithm, "ALGOR_SJF") == 0){
			struct node* temp = ready_queue;
			while (temp != NULL){
				if (temp->proctime < lowest_time){
					pid = temp->pid;
				}
				temp = temp->next;
			}	
			temp = getEntry(temp, pid);
			struct node* process = pop(ready_queue);
		}
	
		printf("Dispatching process with PID %d to running queue...\n", pid);
		running_queue = dispatch(ready_queue, running_queue, pid); // Add in order of pid (start at pid 0)
		timer+=time_delta;
	

		// If ALGOR_RR, use an if statement that takes to a new loop or alter current loop to apply if statements with jiffies

		// Process Simulator - stop when cputime meets or exceeds proctime
		while ((getCpuTime(running_queue, running_queue->pid) != running_queue->proctime) ||
			(getCpuTime(running_queue, running_queue->pid) < running_queue->proctime)){
			
			running_queue->cputime+=time_delta;
			timer+=time_delta;
			
			
			// Add log entry here, add status parameter
		}
		// Note that process has finished and make a log entry
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);
		addLogEntry(running_queue, timer);
		running_queue = processExit(running_queue); // Remove process from running queue
	}
	printf("Total time taken: %f\n", timer);
	// Ready and running should be empty already, just out of caution
	freeList(ready_queue);
	freeList(temp);
	freeList(running_queue);

	return 0;
}

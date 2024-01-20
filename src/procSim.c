#include <stdio.h>
#include "dStruct.h"
#include "procLib.h"

// https://c-for-dummies.com/blog/?p=3246 | Using dirent
// Status Codes:
// 1: Ready
// 2: Running
// 3: Complete

int main(void){
	// Queues
	struct node* ready_queue = NULL; // Queue for processes ready to run
	struct node* running_queue = NULL; // Queue for processes that are running
	// Timing
	double timer = 0.0; // Global timer
	double time_delta = 0.1; // Increment time. Add to cputime for each entry as well
	int pid = 0; // Used to add processes to running queue in order of their addition to ready queue
	
	// Add all processes in the newProc directory to the ready queue
	ready_queue = admit(ready_queue);	
	int size = getSize(ready_queue);
	printf("\n");
		
	while (pid < size){
		// Add process to running queue by PID, remove process from ready queue
		printf("Dispatching process with PID %d to running queue...\n", pid);
		running_queue = dispatch(ready_queue, running_queue, pid); // Add in order of pid (start at pid 0)
		pid++;
		timer+=time_delta;
		
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
	return 0;
}

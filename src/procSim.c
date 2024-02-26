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

int main(void){
	// Queues	
	struct node* ready_queue = NULL; // Holds processes ready to run 
	struct node* running_queue = NULL; // Holds processes that are running		
	// Timing
	double timer = 0.0; // Global timer	
	double time_dt = TIME_DT; // Time increment
	double time_qt = 1.0; // Max allowed time for a process to run before swapping - essentially equal to proctime for SJF and FIFO
	char algorithm[24] = "ALGOR_FIFO"; // Scheduling Algorithm
	
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

	// Add all processes to ready queue	
	ready_queue = admit(ready_queue);
	// Increment time by (time_delta * # of processes)
	printf("\n");

	// Add processes to running queue while all queues are not equal to null
	while (ready_queue){
		// Add process to running queue according to algorithm used, remove process from ready queue
		running_queue = popFromReadyQueue(&ready_queue, algorithm);
		running_queue->status = 2;
		printf("Dispatching process with PID %d to running queue...\n", running_queue->pid);
		addLogEntry(ready_queue, running_queue, timer, filename);

		// Main Process Loop - stop when the process's cputime meets or exceeds proctime
		while ((getCpuTime(running_queue, running_queue->pid) != running_queue->proctime) && 
		      (getCpuTime(running_queue, running_queue->pid) < running_queue->proctime)){	
		
			// Increment global time and add a new log entry for every process in both queues
			timer+=time_dt;
			running_queue->cputime+=time_dt;
			addLogEntry(ready_queue, running_queue, timer, filename);

			// For Round Robin, check if global time has elapsed a jiffy
			if (((strcmp(algorithm, "ALGOR_RR") == 0)) && ((fmod(getCpuTime(running_queue, running_queue->pid), 1.0)) == 0)){
				printf("Rotating process with PID %d to ready queue", running_queue->pid);
				rotate(&ready_queue, &running_queue); // Rotate current process into ready queue
				printf("Dispatching process with PID %d to running queue...\n", ready_queue->pid);
				running_queue = pop(&ready_queue);
			}
		}
		// Note that process has finished and make a log entry
		running_queue->status = 3;
		printf("Process with PID %d ran for %f seconds.\n", running_queue->pid, running_queue->cputime);
		addLogEntry(ready_queue, running_queue, timer, filename);	
		free(running_queue);
		running_queue = NULL;
	}
	printf("Total time taken: %f\n", timer);

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "dStruct.h"

// https://c-for-dummies.com/blog/?p=3246 | Using dirent

// Status Codes:
// 0: Terminated
// 1: Ready
// 2: Running

int main(void){
	// Queues
	struct node* ready_queue = NULL; // Queue for processes ready to run
	struct node* running_queue = NULL; // Queue for processes that are running
	// Timing
	double initial_time = 0.0; // Set cputime to 0 initially
	double time_delta = 0.1; // Increment time. Add to cputime for each entry as well

		
	// Simulating process running
	while (cputime != proctime || cputime < proctime){
		cputime+=time_delta;
	}
	printf("%s finished at %f\n", file->d_name, process->cputime);
	
	return 0;
}

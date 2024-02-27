/* 
Name: Yasir Jami & Cole Doris
360 Lab 5 (Group 4)
*/

#ifndef PROCLIB_H
#define PROCLIB_H

/*
 * Add all valid processes found in newProc directory to ready queue. Delete the files after the processes have been added.
 */
struct node* admit(struct node* ready_queue);

/*
 * Add process to running queue, process will be running and accumulating cputime. Upon cputime meeting/exceeding proctime, removes process from queue.
 */

struct node* dispatch(struct node* ready_queue, struct node* running_queue, int pid);

/*
 * Pop the currently process from running queue upon meeting or exceeding cputime.
 */
struct node* processExit(struct node* running_queue);

/*
 * Appends current status of process as a new log entry to a file located in the log directory 
 */

void addLogEntry(struct node* ready_queue, struct node* running_queue, double time, char* filename);

/*
 * Pop from ready queue according to algorithm
 */
struct node* popFromReadyQueue(struct node** ready_queue, char* algorithm);

/*
 *  Round Robin - rotate process out of running queue and back into ready
 */
void rotate(struct node** ready_queue, struct node** running_queue);

// Scheduling Algorithm Definitions
	#define ALGOR ALGOR_FIFO
	#define TIME_DT 0.1 // Increment timer by this amount each cycle
	#define TIME_JIFFY 1.0 // Time slice at which process rotates out of running queue 

// Macros
	#define str(s) #s
	#define xstr(s) str(s)

#endif

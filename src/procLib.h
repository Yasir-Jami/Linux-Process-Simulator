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
 * Appends status of process as a new log entry to a file located in the log directory 
*/
void addLogEntry(struct node* process, int time);

#endif

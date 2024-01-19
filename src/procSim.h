#ifndef PROCSIM
#define PROCSIM


/*
 * Add process to ready queue. In this queue, process will wait to be added to the running queue.
 */
void admit(struct node* process);

/*
* Add process to running queue, process will be running and accumulating cputime. Upon cputime meeting/exceeding proctime, removes process from queue.
*/

void dispatch(struct node* process);

#endif

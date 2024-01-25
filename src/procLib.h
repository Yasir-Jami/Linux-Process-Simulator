#ifndef PROCLIB_H
#define PROCLIB_H

/* Adds new processes to ready_queue
 *
 */
void admit(struct node* ready_queue);

void dispatch(struct node* running_queue);

void exit();

#endif

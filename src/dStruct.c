#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dStruct.h"

struct node* push(struct node* head, int _pid, int _status, int _niceness, double _cputime, double _proctime, int original_niceness) {
	struct node* newNode;
	if ((newNode = malloc(sizeof(struct node)))==NULL) {
		exit(EXIT_FAILURE);
	}
	newNode->pid= _pid;
	newNode->status = _status;
	newNode->niceness = _niceness;
	newNode->cputime = _cputime;
	newNode->proctime = _proctime;
	newNode->original_niceness = _niceness;

	newNode->next=head;
	return(newNode);
}

struct node* append(struct node** head, struct node** nodeToPush){
	if (head == NULL){
		*head = pop(nodeToPush);
		return *head;
	}

	// Create a new node based on nodeToPush's attributes
	struct node* end_node = NULL;
	if ((end_node = malloc(sizeof(struct node)))==NULL){
		exit(EXIT_FAILURE);
	}
	
	end_node->pid = (*nodeToPush)->pid;
	end_node->status = (*nodeToPush)->status;
	end_node->niceness = (*nodeToPush)->niceness;
	end_node->cputime = (*nodeToPush)->cputime;
	end_node->proctime = (*nodeToPush)->proctime;
	end_node->original_niceness = (*nodeToPush)->niceness;

	struct node* temp = *head;
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = end_node;
	end_node->next = NULL;

	return *head;
}

bool isEmpty(struct node* list){
	if ((list == NULL)){
		printf("List is empty!\n");
		return true;
	}
	return false;
}

// Test multiple pops with valgrind - could be leaking
struct node* pop(struct node** head){
	if (*head == NULL){
		return *head;
	}

	struct node* temp = NULL;
	temp = push(temp, (*head)->pid, (*head)->status, (*head)->niceness, (*head)->cputime, (*head)->proctime, (*head)->niceness);
	if ((*head)->next == NULL){
		free(*head);
		*head = NULL;
		return temp;
	}
	
	(*head) = (*head)->next; // Change head node to next node
	temp->next = NULL; // Break off link to list
	return(temp);
}

// Check for leak when changing connections
struct node* popAtPid(struct node** head, int pid){
	if (isEmpty(*head) == true){
		return *head;
	}
	if ((*head)->pid == pid){
		return pop(head);
	}

	struct node* temp = *head;
	struct node* prev = temp;

	while (temp != NULL){
		if (temp->pid == pid){
			prev->next = temp->next;	
			temp->next = NULL;
			return temp;
		}
		prev = temp;
		temp = temp->next;
	}
	return temp;
}

// Will be O(n) every time - similar to popAtPid, but only pops at end
struct node* popAtEnd(struct node** head){
	if (isEmpty(*head) == true){
		return *head;
	}
	if ((*head)->next == NULL){
		struct node* process = pop(head);
		return process;
	}
	
	struct node* temp = *head;
	struct node* prev = temp;

	while (temp != NULL){
		prev = temp;
		temp = temp->next;
		if (temp->next == NULL){
			prev->next = temp->next;
			temp->next = NULL;
			return pop(&temp);
		}
	}
	return temp;
}

void freeList(struct node* head){
	struct node* temp;
	
	// Free all nodes iteratively
	while (head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
}

// Using default values - for testing dStruct behavior
struct node* initializeList(){	
	struct node* list = NULL;
	list = push(list, 1, 3, 2, 1.2, 10.903, 2);
	list = push(list, 2, 2, 4, 2.1, 32.490, 4);
	list = push(list, 3, 0, 7, 0.03, 3.2930, 7);
	list = push(list, 4, 1, 4, 4.5, 1.3849, 4);
	list = push(list, 5, 1, 8, 2.3, 449.2492, 8);
	list = push(list, 6, 4, 0, 7.2, 2.482902, 0);
	return list;
}

int getSize(struct node* list){
	if (isEmpty(list) == true){
		return 0;
	}

	struct node* temp = list;
	int i = 0;

	while (temp != NULL){
		i++;
		temp = temp->next;
	}
	return i;
}

struct node* getEntry(struct node* list, int pid){
	if (isEmpty(list) == true){
		return list;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp;
		}
		temp = temp->next;
	}
	return list; // No PID match --> entry not found
}

/* struct node* to be used in each function since we are looking through a given list*/

struct node* getEntryByIndex(struct node* list, int ind){
	if (isEmpty(list) == true){
		return list;
	}

	int i = 0;
	struct node *temp = list;
	while (temp != NULL || i != ind){
		if (i == ind) {
			return temp;
		}
		temp = temp->next;
		i++;
	}

	return temp;
}

int getNiceness(struct node* list, int pid){
	if (isEmpty(list) == true){
		return -1;
	}

 	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->niceness;
		}
		temp = temp->next;
	}
	return -1; // PID does not exist
}

void setNiceness(struct node* list, int pid, int new_niceness){
	if (isEmpty(list) == true){
		return;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			temp->niceness = new_niceness;
		}
		temp = temp->next;
	}
}

int getStatus(struct node* list, int pid){
	if (isEmpty(list) == true){
		return -1;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->status;
		}
		temp = temp->next;
	}
	return -1; // PID does not exist
}

void setStatus(struct node* list, int pid, int new_status){
	if (isEmpty(list) == true){
		return;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			temp->status = new_status;
		}
		temp = temp->next;
	}
}

double getCpuTime(struct node* list, int pid){
	if (isEmpty(list) == true){
		return -1.0;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->cputime;
		}
		temp = temp->next;
	}
	return -1.0; // PID does not exist
}

void setCpuTime(struct node* list, int pid, double new_cputime){
	if (isEmpty(list) == true){
		return;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			temp->cputime = new_cputime;
		}
		temp = temp->next;
	}
}

double getProcTime(struct node* list, int pid){
	if (isEmpty(list) == true){
		return -1.0;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->proctime;
		}
		temp = temp->next;
	}
	return -1.0; // PID does not exist
}


bool find(struct node* list, int pid){
	if (isEmpty(list) == true){
		return false;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return true;
		}
		temp = temp->next;
	}
	return false;
}

bool findByNiceness(struct node* list, int niceness){
	if (isEmpty(list) == true){
		return false;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->niceness == niceness){
			return true;
		}
		temp = temp->next;
	}
	return false;
}

bool findByStatus(struct node* list, int status){
	if (isEmpty(list) == true){
		return false;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->status == status){
			return true;
		}
		temp = temp->next;
	}
	return false;
}

/*If at least one entry with the given niceness exists*/

void printEntry(struct node* list, int pid){
	struct node* entry = getEntry(list, pid); // Function quits if index is larger than list or list is empty
	printf("pid: %i\n", entry->pid);
	printf("status: %i\n", entry->status);
	printf("niceness: %i\n", entry->niceness);
	printf("cputime: %f\n", entry->cputime);
	printf("proctime: %f\n\n", entry->proctime);
}

void printEntries(struct node* list) {
	if (isEmpty(list) == true){
		return;
	}

	struct node* temp = list;	
	while (temp != NULL) {
		printEntry(list, temp->pid);
		temp = temp->next;
	}
}

void printByNiceness(struct node* list, int niceness){
	if (isEmpty(list) == true){
		return;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->niceness == niceness){
			printEntry(list, temp->pid);
		}
		temp = temp->next;
	}
	return;
}

void printByStatus(struct node* list, int status){
	if (isEmpty(list) == true){
		return;
	}

	struct node *temp = list;
	while (temp != NULL){
		if (temp->status == status){
			printEntry(temp, temp->pid);
		}
		temp = temp->next;
	}
	return;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dStruct.h"

struct node* push(struct node* list, int _pid, int _status, int _niceness, float _cputime, float _proctime) {
	struct node* newNode;
	if ((newNode = malloc(1*sizeof(struct node)))==NULL) {
		exit(EXIT_FAILURE);
	}
	newNode->pid= _pid;
	newNode->status = _status;
	newNode->niceness = _niceness; 
	newNode->cputime = _cputime;
	newNode->proctime = _proctime;
	
	newNode->next=list;
	return(newNode);
}

struct node* pop(struct node* list) {
	struct node* currentNode;
	currentNode = list->next;
	//if(currentNode==NULL) {
	//	return(list);
	//}
	free(list);
	return(currentNode);
}

// Using default values
struct node* initializeList(){
	struct node* list = NULL; // NULL: void*
	list = push(list, 6, 0, 0, 0.0, 0.0);
	list = push(list, 5, 0, 0, 0.0, 0.0);
	list = push(list, 4, 0, 0, 0.0, 0.0);
	list = push(list, 3, 0, 0, 0.0, 0.0);
	list = push(list, 2, 0, 0, 0.0, 0.0);
	list = push(list, 1, 0, 0, 0.0, 0.0);

	return list;
}

bool isEmpty(struct node* list){
	if (list == NULL){
		printf("List is empty!\n");	
		return true;
	}
	return false;
}

struct node* getEntry(struct node* list, int pid){
	struct node *temp;
	
	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp;
		}
		temp = temp->next;
	}
	exit(EXIT_FAILURE);
}

/* struct node* to be used in each function since we are looking through a given data structure*/

struct node* getEntryByIndex(struct node* list, int ind){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}

	int i = 0;
	temp = list;	
	while (temp != NULL || i == ind){	
		temp = temp->next;
		i++;
	}
	
	// If index is larger than list size, it will be null
	if (temp == NULL){
		exit(EXIT_FAILURE);
	}

	return temp;
} 

int getNiceness(struct node* list, int pid){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->niceness;
		}
		temp = temp->next;
	}
	exit(EXIT_FAILURE); // PID does not exist
}


void setNiceness(struct node* list, int pid, int new_niceness){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			temp->niceness = new_niceness;
		}
		temp = temp->next;
	}
}

int getStatus(struct node* list, int pid){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->status;
		}
		temp = temp->next;
	}
	exit(EXIT_FAILURE); // PID does not exist
}

void setStatus(struct node* list, int pid, int new_status){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			temp->status = new_status;
		}
		temp = temp->next;
	}
}

float getCpuTime(struct node* list, int pid){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp->cputime;
		}
		temp = temp->next;
	}
	exit(EXIT_FAILURE); // PID does not exist
}

void setCpuTime(struct node* list, int pid, float new_cputime){
	struct node *temp;

	if (isEmpty(list) == true){
		exit(EXIT_FAILURE);
	}
	
	temp = list;
	while (temp != NULL){
		if (temp->pid == pid){
			temp->cputime = new_cputime;
		}
		temp = temp->next;
	}
}

void printEntry(struct node* list, int ind){
	printf("Print Entry"); // Placeholder
	
}


void printEntries(struct node* list) {
	if (list == NULL) {
	    printf("List is empty!\n\n");
	} else { 
	    for(;list->next !=NULL;list = list->next) {
	        printf("pid: %i\n", list->pid);
		    printf("status: %i\n", list->status);
		    printf("niceness: %i\n", list->niceness);
		    printf("cputime: %f\n", list->cputime);
		    printf("proctime: %f\n\n", list->proctime);
	   }
	   printf("pid: %i\n", list->pid);
	   printf("status: %i\n", list->status);
	   printf("niceness: %i\n", list->niceness);
	   printf("cputime: %f\n", list->cputime);
	   printf("proctime: %f\n\n", list->proctime);
	}    
}

// Fix setters and review code/add comments

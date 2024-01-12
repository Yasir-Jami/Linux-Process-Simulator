#include <stdio.h>
#include <stdlib.h>
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
void initializeList(){
	list = NULL; // NULL: void*
	list = push(list, 6, 0, 0, 0.0, 0.0);
	list = push(list, 5, 0, 0, 0.0, 0.0);
	list = push(list, 4, 0, 0, 0.0, 0.0);
	list = push(list, 3, 0, 0, 0.0, 0.0);
	list = push(list, 2, 0, 0, 0.0, 0.0);
	list = push(list, 1, 0, 0, 0.0, 0.0);
}

bool isEmpty(struct node*){
	if (node* == NULL){
		printf("List is empty!\n");	
		return 0;
	}
	return 1;
}

struct getEntry(struct node* head, int pid){
	struct node *temp;
	
	if (isEmpty(list) == 0){
		return EXIT_FAILURE;
	}
	
	temp = head;
	while (temp != NULL){
		if (temp->pid == pid){
			return temp;
		}
		temp = temp->next;
	}
	return EXIT_FAILURE;
}

/* struct node* head - to be used in each function, we are looking through a given data structure*/

struct getEntryByIndex(struct node* head, int ind){
	struct node *temp;

	if (isEmpty(list) == 0){
		return EXIT_FAILURE;
	}

	temp = head;
	while (temp != NULL){
		
	}
	
	
} 

int getNiceness(int pid);

int setNiceness(int pid);

int getStatus(int pid);

int setStatus(int pid);

float getCpuTime(int pid);

float setCpuTime(int pid);


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



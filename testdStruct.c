#include <stdio.h>
#include <stdlib.h> 
#include "dStruct.h"

int main(void) {
	struct node* list = initializeList();

	printf("List before changing\n");
	printEntries(list);	
	printf("###########################################\n");

	struct node* entry = pop(list);

	//struct node* entry2 = pop(list);

	struct node* emptylist = NULL;

	isEmpty(emptylist);

	printf("Popped Entry: \n");
	printEntry(entry, entry->pid);

	printf("###########################################");

	//printf("Popped Entry: \n");
	//printEntry(entry2, entry2->pid);

	printf("###########################################\n");

	printEntries(list);

//	printf("Current PID: %d", list2->pid);


	//printEntry(list, 2);
	/*
	printEntries(list);
	list = pop(list);	
		
	printEntries(list);
	
	list = push(list, 124, 0, 0, 0.0, 0.0);
	
	printEntries(list);
	*/
	// waow
}

#include <stdio.h>
#include <stdlib.h> 
#include "dStruct.h"

int main(void) {
	struct node* list = initializeList();

	struct node* entry = getEntryByIndex(list, 0);

	//printEntries(list);

	printByStatus(list, 1);

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

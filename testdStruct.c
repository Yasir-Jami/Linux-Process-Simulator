#include <stdio.h>
#include <stdlib.h> 
#include "dStruct.h"

int main(void) {
	struct node* list = initializeList();
	
	printEntries(list);
	list = pop(list);	
		
	printEntries(list);
	
	list = push(list, 124, 0, 0, 0.0, 0.0);
	
	printEntries(list);
	// waow
}

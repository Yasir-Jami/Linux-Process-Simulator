#include <stdio.h>
#include <stdlib.h> 

int main(void) {
	struct node* list = initializeList();
	
	printList(list);
	list = pop(list);	
		
	printList(list);
	
	list = push(list, 124, 0, 0, 0.0, 0.0);
	
	printList(list);
	// waow
}

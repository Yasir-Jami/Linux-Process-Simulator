#include <stdio.h>
#include "dStruct.h"

int main(void){
	struct node* queue1 = NULL;	
	queue1 = initializeList();
	
	printEntries(queue1);
	
	struct node* remove = pop(queue1);
	//struct node* remove2 = pop(queue1);
	printf("**********AFTER POP**********\n");
	printEntries(queue1);

	freeList(queue1);
	//freeList(remove);

	return 0;
}

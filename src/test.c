#include <stdio.h>
#include "dStruct.h"

int main(void){
	struct node* queue1 = NULL;	
	queue1 = initializeList();	
	//printEntries(queue1);
	
	printf("Current q1 size: %d\n", getSize(queue1));

	struct node* remove = pop(queue1);
	printf("**********AFTER POP**********\n");
	printf("New q1 size: %d\n", getSize(queue1));
	//printEntries(queue1);

	printf("New remove size: %d\n", getSize(remove));

	queue1 = pop(remove);

	printf("New q1 size: %d\n", getSize(queue1));
	printf("New remove size: %d\n", getSize(remove));

	freeList(queue1);
	//printEntries(remove);
	//freeList(remove);
	return 0;
}

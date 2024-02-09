#include <stdio.h>
#include "dStruct.h"

int main(void){
	struct node* queue1 = NULL;	
	queue1 = initializeList();
/*	
	printf("Current q1 size: %d\n", getSize(queue1));
	printEntries(queue1);
	struct node* remove = pop(queue1);
	remove = pop(queue1);
	remove = pop(queue1);
	remove = pop(queue1);

	printf("**********AFTER POP**********\n");
	printf("New q1 size: %d\n", getSize(queue1));
	printEntries(queue1);
	
	printf("New remove size: %d\n", getSize(remove));
	printEntries(remove);

	freeList(queue1);
*/
	//printEntries(remove);
	//freeList(remove);

/*
	struct node* queue2 = popAtPID(queue1, 3);
	printf("Queue1 after pop:\n");
	printEntries(queue1);
	printf("Queue2 after pop:\n");
	printEntries(queue2);
	
	freeList(queue1);
	printf("Queue1 after queue1 free\n");
	printEntries(queue1);

	printf("Queue2 after queue1 free\n");
	printEntries(queue2);
*/
	struct node* queue3 = popAtPID(queue1, 1);
	printf("Queue1 after pop:\n");	
	printEntries(queue1);

	printf("Queue3 after pop:\n");	
	printEntries(queue3);


	return 0;
}

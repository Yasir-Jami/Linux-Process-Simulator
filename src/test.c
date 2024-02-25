#include <stdio.h>
#include "dStruct.h"

//void moveToEnd(struct** node);

void moveToEnd(struct node** queue){
	int i = 0;
	while (*queue != NULL){	
		*queue = (*queue)->next;
		i++;
	}
}

int main(void){
	struct node* queue1 = initializeList();

	//printf("Before queue1 node removal:\n");
//	printEntries(queue1);

	struct node* queue2 = pop(&queue1);
	//moveToEnd(&queue1);

	//printEntries(queue1);
	//printEntries(queue2);
	struct node* queue3 = pop(&queue2);

	queue2 = pop(&queue3);
	queue3 = pop(&queue2);

	printf("Queue 2 Status:\n");
	printEntries(queue2);
	printf("Queue 3 Status:\n");
	printEntries(queue3);

	return 0;
}

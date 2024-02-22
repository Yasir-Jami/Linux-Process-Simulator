#include <stdio.h>
#include "dStruct.h"


void moveToEnd(struct node queue){
	int i = 0;
	while (queue != NULL){
		printf("%d ", i);
		i++;
	}
}


int main(void){
	struct node* queue1 = initializeList();
	
	//printEntries(queue1);

	moveToEnd(&queue1);

	printEntries(queue1);
}

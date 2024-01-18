#include <stdio.h>
#include <stdlib.h>
#include "dStruct.h"

int main(void) {


	struct node* list = initializeList();
	printf("Initializing an example list: \n");
	printEntries(list);
	printf("\n");

	printf("Getting entry by pid: 1. ");
	struct node* anEntry = getEntry(list, 1);
	printf("status: %i. niceness: %i. cputime: %f. proctime: %f", anEntry->status, anEntry->niceness, anEntry->cputime, anEntry->proctime);
	printf("\n");

	printf("Getting first entry (index: 0)");
	anEntry = getEntryByIndex(list, 0);
	printf("pid: %i. status: %i. niceness: %i. cputime: %f. proctime: %f\n", anEntry->pid, anEntry->status, anEntry->niceness, anEntry->cputime, anEntry->proctime);

	printf("Pushing new entry:\n");
	push(list, 9, 3, 2, 1.03, 9.99);
	printEntries(list);

	printf("\n\nPopping an entry:\n");
	list = pop(list);
	list = pop(list);
	printEntries(list);

	double aTime = getCpuTime(list, 1);
	printf("Cputime of entry pid 1: %f\n", aTime);
	printf("setting Cputime of entry pid 1 to 1.23: ");
	setCpuTime(list, 1, 1.23);
	aTime = getCpuTime(list, 1);
	printf("%f\n", aTime);

	int aNiceness = getNiceness(list,1);
	printf("Niceness of entry pid 1: %i \n", aNiceness);
	setNiceness(list, 1, 40);
	aNiceness = getNiceness(list,1);
	printf("Setting niceness of entry pid 1 to 40: %i \n", aNiceness);


	int aStatus = getStatus(list, 1);
	printf("Status of entry pid 1: %i \n", aStatus);
	setStatus(list, 1, 20);
	aStatus = getStatus(list, 1);
	printf("Setting status of entry pid 1 to 20: %i \n", aStatus);


	printf("Finding entry by pid 3: \n");
	if (find(list,3)) {
		printf("Entry found!\n");
	} else {
		printf("Nope.\n");
	}

	printf("Finding entry by pid 3232913298: \n");
	if (find(list,3232913298)) {
		printf("Entry found!\n");
	} else {
		printf("Nope.\n");
	}

	printf("Finding entry by niceness 4: \n");
	if (findByNiceness(list,4)) {
		printf("Entry found\n");
	} else {
		printf("Nope.\n");
	}

	printf("Finding entry by status: 2\n");
	if (findByStatus(list,2)) {
		printf("Entry found\n");
	} else {
		printf("Nope.\n");
	}

	printf("Printing by status 2\n");
	printByStatus(list, 2);

	printf("printing by niceness 4\n");
	printByNiceness(list, 4);

	// waow
}

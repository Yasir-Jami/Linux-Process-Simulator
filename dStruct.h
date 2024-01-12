#ifndef DSTRUCT 
#define DSTRUCT

/* Node struct for linked list and List Initialization */
struct node {
	int pid;
	int status;
	int niceness;
	int cputime;
	int proctime;
	struct node* next;
};

void initializeList;

/* Data Structure (linked list) Operations */
struct node* push(struct node*, int, int, int, float, float);

struct node* pop(struct node*);

/* Getters and Setters */
struct getEntry(int pid);

struct getEntryByIndex(int ind); 

int getNiceness(int pid);

int setNiceness(int pid);

int getStatus(int pid);

int setStatus(int pid);

float getCpuTime(int pid);

float setCpuTime(int pid);

/* Search Functions */
bool find(int pid);

bool findByNiceness(int niceness); /*If at least one entry with the given niceness exists*/

bool findByStatus(int status);

/* Print Functions*/
void printEntries(struct node*); /*Print all entries*/

void printEntry(int pid);

void printByNiceness(int niceness);

void printByStatus(int status);

#endif

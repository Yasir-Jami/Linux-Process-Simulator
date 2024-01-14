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
struct getEntry(struct node*, int pid);

struct getEntryByIndex(struct node*, int ind); 

int getNiceness(struct node*, int pid);

void setNiceness(struct node*, int pid);

int getStatus(struct node*, int pid);

void setStatus(struct node*, int pid);

float getCpuTime(struct node*, int pid);

void setCpuTime(struct node*, int pid);

/* Search Functions */
bool find(struct node*, int pid);

bool findByNiceness(struct node*, int niceness); /*If at least one entry with the given niceness exists*/

bool findByStatus(struct node*, int status);

/* Print Functions*/
void printEntries(struct node*); /*Print all entries*/

void printEntry(struct node*, int pid);

void printByNiceness(struct node*, int niceness);

void printByStatus(struct node*, int status);

#endif

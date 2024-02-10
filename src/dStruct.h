#ifndef DSTRUCT 
#define DSTRUCT

#include <stdbool.h> // Required for bool functions

/* Node struct for linked list and List Initialization */
struct node {
	int pid;
	int status;
	int niceness;
	double cputime;
	double proctime;
	struct node* next;
};

struct node* initializeList();

/* Data Structure (linked list) Operations */
struct node* push(struct node*, int, int, int, double, double);

struct node* pushToEnd(struct node* head, struct node* new_end_node);

struct node* pop(struct node*);

struct node* popAtPID(struct node* head, int pid);

struct node* popAtEnd(struct node* head);

void freeList(struct node* head);

int getSize(struct node*);

/* Getters and Setters */
struct node* getEntry(struct node*, int pid);

struct node* getEntryByIndex(struct node*, int ind); 

int getNiceness(struct node*, int pid);

void setNiceness(struct node*, int pid, int new_niceness);

int getStatus(struct node*, int pid);

void setStatus(struct node*, int pid, int new_status);

float getCpuTime(struct node*, int pid);

void setCpuTime(struct node*, int pid, double new_cputime);

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

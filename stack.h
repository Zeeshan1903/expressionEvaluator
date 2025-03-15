/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	Aim: 		Header file stack.c
*/

#ifndef Stack_H
#define Stack_H

// Integer Stack 
typedef struct {
	int* data;		// Array of integeris. Space will be allocated by init()
	int capacity;	// Max capacity of stack
	int top;		// Index of next empty location
} iStack;

void init_is(iStack* s, int capacity);
/* 
	Inputs: An iStack pointer and the required capacity
	Action: Allocates required memory for s->data
	Exit behaviour: Message to stderr and exit
*/

void free_is(iStack *s);
/* 
	Inputs: An iStack pointer s
	Action: Frees the memory allocated for s->data
*/

void push_is(iStack* s, int data);
/* 	
	Inputs: An iStack pointer s and an integer data
	Action: 
		If s is not full, 
			-	push data to s
		If s is full, 
			-	double the capacity of stack and 
			-	then push the data to s
	Exit behaviour: Message to stderr and exit
*/

int pop_is(iStack *s);
/*
	Input: An iStack pointer s
	Action: 
		If s is not empty,
			-	pop the stack and 
			-	return the popped value
		If s is empty,
			=	Message to stderr and
			-	return INT_MIN
*/

int isempty_is(iStack *s);
/*
	Input: An iStack pointer s
	Output: 1 if s is empty and 0 otherwise
*/

// Void Pointer Stack
typedef struct {
	void ** pointers;	// An array of pointers. Space to be allocated by init()
	int capacity;		// Max capacity of stack
	int top;			// Index of next empty location
} pStack;

void init_ps(pStack* s, int capacity);
/* 
	Inputs: A pStack pointer and the required capacity
	Action: Allocates required memory for s->pointers
	Exit behaviour: Message to stderr and exit
*/

void free_ps(pStack *s);
/* 
	Inputs: A pStack pointer s
	Action: Frees the memory allocated for s->pointers
*/

void push_ps(pStack* s, void* p);
/* 	
	Inputs: A pStack pointer s and a void pointer p 
	Action: 
		If s is not full, 
			-	push p to s
		If s is full, 
			-	double the capacity of stack and 
			-	then push the p to s
	Exit behaviour: Message to stderr and exit
*/

void* pop_ps(pStack *s);
/*
	Input: An iStack pointer s
	Action: 
		If s is not empty,
			-	pop the stack and 
			-	return the popped value
		If s is empty,
			=	Message to stderr and
			-	return INT_MIN
*/

int isempty_ps(pStack *s);
/*
	Input: A pStack pointer s
	Output: 1 if s is empty and 0 otherwise
*/


#endif

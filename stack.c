/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	
	Aims:		1. Implement an integer Stack ADT over Array Data Structure
					(All data to be stored are integers)
				2. Implement a pointer Stack ADT over Array Data Structure
					(All data to be stored are void pointers)
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <limits.h>	// Needed for INT_MIN
#include "stack.h"

// Integer Stack

void init_is(iStack* s, int capacity) {
	s->data = (int*) malloc(capacity * sizeof(int));
	if (s->data == NULL) {
		fprintf(stderr, "Error in init_is: Memory Allocation Failed\n");
		exit(1);
	}
	s->capacity = capacity;
	s->top = 0;	// index of next empty location 
	 // printf("Stack of capacity %d initialized.\n", capacity);
}

void free_is(iStack *s) {
	free(s->data);
	return;
}

void push_is(iStack* s, int data) {
	if (s->top >= s->capacity) {
		s->data = (int*) realloc((void *) s->data, 2*s->capacity*sizeof(int));
		if (s->data == NULL) {
			fprintf(stderr, "Error in push_is: Memory Expansion Failed\n");
			exit(1);
		}
		s->capacity *= 2;
	}

	s->data[s->top] = data;
	s->top++;
	// printf("Push %d\n", data);

}

int pop_is(iStack *s) {
	if (s->top <= 0) {
		fprintf(stderr, "Error in pop_is: Stack Empty\n");
		return INT_MIN;
	}
	
	s->top--;
	int data = s->data[s->top];				
	// printf("Pop  %d\n", data);
	return data;

}

int isempty_is(iStack *s) {
	if(s->top == 0)
		return 1;
	else
		return 0;
}
	
// Void Pointer Stack

void init_ps(pStack* s, int capacity) {
	s->pointers = (void**) malloc(capacity * sizeof(void*));
	if (s->pointers == NULL) {
		fprintf(stderr, "Error in init_ps: Memory Allocation Failed\n");
		exit(1);
	}
	s->capacity = capacity;
	s->top = 0;	// index of next empty location 
	// printf("Pointer Stack of capacity %d initialized.\n", capacity);
}

void free_ps(pStack *s) {
	free(s->pointers);
	return;
}

void push_ps(pStack* s, void* p) {
	if (s->top >= s->capacity) {
		s->pointers = (void**) realloc((void*) s->pointers, 2*s->capacity*sizeof(void*));
		if (s->pointers == NULL) {
			fprintf(stderr, "Error in push_ps: Memory Expansion Failed\n");
			exit(1);
		}
		s->capacity *= 2;
	}
	s->pointers[s->top] = p;
	s->top++;
}

void* pop_ps(pStack *s) {
	if (s->top <= 0) {
		fprintf(stderr, "Error in pop_ps: Stack Empty\n");
		return NULL;
	}
	
	s->top--;	
	return s->pointers[s->top];
}
 
// Testing code 
int test() {
	iStack s;
	init_is(&s, 16);


	pStack ps;
	init_ps(&ps, 16);

	for(int i = 0; i < 26; i++) {
		push_is(&s, i);
		push_ps(&ps, &i);
		printf("Push %d to iStack and %p to pStack\n", i, &i);
	}

	for(int i = 0;; i++) {
		int data = pop_is(&s);
		int* pointer = pop_ps(&ps);
		if (data == INT_MIN) {
			printf("\n");
			break;
		}
		printf("Pop %d from iStack and %p from pStack\n", data, pointer);
	}

	return 0;
}


int isempty_ps(pStack *s) {
	if(s->top == 0)
		return 1;
	else
		return 0;
}
	

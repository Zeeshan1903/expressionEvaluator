/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	
	Aim: 		Helper functions for tokeniser and expression trees
*/

#include <stdio.h>
#include <stdlib.h>	// Needed for malloc, free etc
#include <ctype.h>	// Needed for isdigit
#include <string.h>	// Needed for strlen, atoi
#include "token.h"

	const char legalOps[] 	= "+-*/~";	// Unary minus is ~
	const char legalParOpen[] 	= "([{";
	const char legalParClose[] 	= ")]}";

/* Function to convert a string to an array of tokens */
Token* tokenise(char* str) {
/*	
	Inputs: A string str to be tokenised
	Output: An array of tokens extracted from the string, ending with an
			EoS (End of String) token.
	Error Response:
		If memory allocation fails - prints error message to stderr and returns NULL
		If any invalid token is found - prints error message to stderr and returns NULL
*/	

	// Allocate memory for the token array. 
	// The maximum requirement is bounded by the length of str + 1
	int maxTokens = strlen(str) + 1;
	Token* ta = (Token *) malloc(maxTokens * sizeof(Token));
	if(ta == NULL) {
		fprintf(stderr, "Error: Memory allocation for token array failed\n");
		return NULL;
		}

	int i = 0;
	while(*str != '\0') {

		//Skip over white spaces
		while(isspace(*str))
			str++;

		if (strchr(legalOps, *str) != NULL) {
			ta[i].type = operator;
			ta[i].op = *str;
			str++;
		}	
		else if (strchr(legalParOpen, *str) != NULL) {
			ta[i].type = parOpen;
			ta[i].op = *str;
			str++;
		}	
		else if (strchr(legalParClose, *str) != NULL) {
			ta[i].type = parClose;
			ta[i].op = *str;
			str++;
		}	
		else if (isdigit(*str)) {
			ta[i].type = operand;
			ta[i].value = atoi(str);
			// Skip over the consecutive digits
			while(isdigit(*str))
				str++;
		}	
		else {
			fprintf(stderr, "Error: Found invalid token in string.\n");
			return NULL;
		}
		i++	;
	}

	ta[i].type = EoS;
	return ta;
}

/* Function to print an array of tokens */
void print_tokens(Token *ta) {
	printf("Tokens\n");
	while(ta->type != EoS) {
		if(ta->type == operator)
			printf("%c\t operator\n", ta->op);
		else if(ta->type == parOpen)
			printf("%c\t parOpen\n", ta->op);
		else if(ta->type == parClose)
			printf("%c\t parClose\n", ta->op);
		else if(ta->type == operand)
			printf("%d\t operand\n", ta->value);
		else
			printf("\t Invalid Token\n");
		ta++;
	}
}

/* Function to create a node of an expression tree */
eTree* create_node(Token token, eTree* left, eTree* right) {
/*
	Inputs:
		1. 	Token to be stored in the new node to be inserted
		2.	An eTree pointer to be set as the left child
		3.	An eTree  pointer to be set as the right child
	Actions:
		1.	Memory required for a new node is allotted.
		2.	The data and the child pointers of the new node are set from the inputs
	Error Response:
		1.	Prints "Error: Memory allocation for new node failed." to stderr if
			malloc fails.	
		2.	Returns NULL if the new node cannot be created
*/
	eTree* new = (eTree *) malloc(sizeof(eTree));

	new->token 	= token;
	new->left 	= left;
	new->right 	= right;

	return new;
	
}

/* Function to free the memory allotted to an expression tree */
void free_etree(eTree* t) {
	if (t == NULL)
		return;
	else {
		free_etree(t->left);
		free_etree(t->right);
		free(t);
		return;
	}
}

/*	Helper function to print one level of a binary tree
*/
void print_level(eTree* t, int t_level, int p_level, int height) {
/*
	Inputs:
		1.	Top level node t
		2.	Height of the top level node (t) in the whole binary tree
		3.	Level of the binary tree to be printed
		4.	Height of the whole binary tree
*/
	if(t_level > p_level) {
		fprintf(stderr, "Error in print_level\n");
		return;
		}
	if(t_level < p_level) {
		if (t != NULL)
			print_level(t->left, t_level+1, p_level, height);
		else
			print_level(NULL, t_level+1, p_level, height);

		if (t != NULL)
			print_level(t->right, t_level+1, p_level, height);
		else
			print_level(NULL, t_level+1, p_level, height);
		return;
	}

	// t_level == p_level
	int padding = 1;	// for alignment
	for (int i = p_level; i < height-1; i++)
		padding = padding * 2 + 1;

	// To prefix some space and a line 
	for (int i = 0; i < (padding+1)/2; i++)
		printf("  ");
	for (int i = (padding+1)/2; i < padding; i++)
		printf("__");

	if (t != NULL){
		if(t->token.type == operand)	
			printf("%2d", t->token.value);	
		if(t->token.type == operator)	
			printf("%2c", t->token.op);	
	}
	else
		printf("()");	

	// To suffix a line and some space
	for (int i = (padding+1)/2; i < padding; i++)
		printf("__");
	for (int i = 0; i < (padding+1)/2; i++)
		printf("  ");

	printf("  ");
	return;
}

/* Helper function to return the height of a binary tree */
int height(eTree *t) {
	if (t == NULL)
		return 0;
	else {
		int hl 	= height(t->left);
		int hr 	= height(t->right);
		int hmax = (hl > hr) ? hl : hr;
		return hmax + 1;
	}
}
/*	Helper function to print the binary tree in a tree-like way.
*/
void print_etree(eTree* t) {
	int h = height(t);
	for(int l = 0; l < h; l++) {
		print_level(t, 0, l, h);
		printf("\n");
		}
	return;
}



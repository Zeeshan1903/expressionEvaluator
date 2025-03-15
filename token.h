/*
	Course:		CS2130 DSA Lab 
	Semester:	2024 Jan-Apr
	
	Aim: 		Helper functions for tokeniser and expression trees
*/

#ifndef TOKEN_H
#define TOKEN_H

enum tokenType {operand, operator, parOpen, parClose, EoS};

typedef struct Token {
	enum tokenType type; 
    int 	value;
	char 	op;
} Token;		

typedef struct eTree {
	Token token;
	struct eTree* left;
	struct eTree* right;
} eTree;

/* Function to convert a string to an array of tokens */
Token* tokenise(char* str);
/*	
	Inputs: A string str to be tokenised
	Output: An array of tokens extracted from the string, ending with an
			EoS (End of String) token.
	Error Response:
		If memory allocation fails - prints error message to stderr and returns NULL
		If any invalid token is found - prints error message to stderr and returns NULL
*/	

/* Function to print an array of tokens */
void print_tokens(Token *ta);

/* Function to create a node of an expression tree */
eTree* create_node(Token token, eTree* left, eTree* right);
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

/* Function to free the memory allotted to an expression tree */
void free_etree(eTree* t);
/*
	Input: Root node of the expression tree
*/

/* Function to display an expression tree */
void print_etree(eTree* t);
/*
	Input: Root node of the expression tree
*/

#endif

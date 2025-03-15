/*
    Name:        <full name>
    Roll No:    <roll number>
    Course:        CS2130 DSA Lab
    Semester:    2024 Jan-Apr
    Lab:        Week 9
    Tasks:        Infix to Postfix Conversion using Shunting Yard Algorithm
    Aim:         Convert an infix expression to postfix expression
*/

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include<stdlib.h>
#include "stack.h"
#include "token.h"


/* Function to return the precedence of an operator */
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '~': // Unary negation has higher precedence
            return 3;
        default:
            return 0; // For parentheses and other characters
    }
}


/* Task 1. Evaluate a given fully parenthesised infix expression
*/
int infix_eval(char *str) {
/*
    Input:     A fully parenthesised infix expression
    Output: The result of evaluating the expression
    Steps:
        1.    Tokenise str to get a token array (say ta)
        2.    Declare and initialise an operand stack (say valStack) of required size
            (num of tokens in ta is one way to estimate the size)
        3.    Declare and initialise an operator stack (say opStack) of required size
            (num of tokens in ta is one way to estimate the size)
            (int stack can also hold characters)
        3.    Linearly process ta till you hit a token of type EoS
            a)     If the current token is an operand, push the value to valStack
            b)     If the current token is a parOpen, push the paranthesis to opStack
            c)     If the current token is an operator  push the operator (char) to opStack
            d)     If the current token is a parClose then do the following computation
                - pop opStack and store the result in a character op
                -    If op is '('
                    -    Skip over it
                -    Else If op is the unary negation ~
                    -    pop valStack once,
                        (return INT_MIN the token scan if you get INT_MIN as value)
                    -    negate the popped value, and
                    -    push the result back to valStack
                -    Else If op is a binary operator
                    -    pop valStack twice to get val2 and val1 (in that order)
                        (return INT_MIN the token scan if you get INT_MIN as either value)
                    -    compute the result = val1 operator val2 using a switch case
                        on the operator, and
                    -    push the result back to valStack
                -    pop opStack once more and confirm that it is '('
                    Otherwise return INT_MIN
        4.    If the current token is EoS, the final result can be popped from
            the valStack.
            Otherwise the token processing was not complete. In this case,
            free the stacks and return INT_MIN
        5.    Now check that the valStack and opStack are empty to make sure that
            the expression was valid.
            Otherwise the token processing was not complete. In this case,
            free the stacks and return INT_MIN

    Error repsonse:     Print the following error messages to stderr and return INT_MIN
        1. Tokenise error:  "Error: Could not tokenise <str>. Returning <INT_MIN>.\n"
        2. Evalution error: "Error in infix_eval: Invalid infix expression\n"
*/
    Token*    ta = tokenise(str);
    if(ta == NULL){
        fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
        return INT_MIN;
    }

    int numTokens = 0;
    while(ta[numTokens++].type != EoS);

    iStack valStack;
    init_is(&valStack, numTokens);

    iStack opStack;        // Integer stack can also hold characters
    init_is(&opStack, numTokens);
    
    // Task 1. Solution

    int index = 0;
    while(ta[index].type != EoS){
        if(ta[index].type == operand)push_is(&valStack, ta[index].value);
        else if(ta[index].type == parClose){
            char op = pop_is(&opStack);
            int result ;
            if( op == '~'){
                int val1 = pop_is(&valStack);
                if(val1 == INT_MIN)return INT_MIN;
                result = -1 * val1;
                
                
            }
            else if(op == '+'){
                int val1 = pop_is(&valStack);
                int val2 = pop_is(&valStack);
                if(val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;

                result = val1 + val2;
            }
            else if(op == '-'){
                int val2 = pop_is(&valStack);
                int val1 = pop_is(&valStack);
                if(val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;

                result = val1 - val2;
            }   
            else if(op == '*'){
                int val2 = pop_is(&valStack);
                int val1 = pop_is(&valStack);
                if(val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;

                result = val1 * val2;               
            }
            else if(op == '/'){
                int val2 = pop_is(&valStack);
                int val1 = pop_is(&valStack);
                if(val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;

                result = val1 / val2;   
            }
            if(pop_is(&opStack) != '(')return INT_MIN;
            push_is(&valStack, result);
        }
        else if(ta[index].type == operator || ta[index].type == parOpen)push_is(&opStack, ta[index].op);

        index++;
    }

    int result = pop_is(&valStack);

    if(!isempty_is(&valStack) || !isempty_ps(&opStack)) return INT_MIN;

    
    
    free_is(&valStack);
    free_is(&opStack);
    
    return result;
    // return INT_MIN; // You may want to edit this
}



/* Task 2. Convert a given fully parenthesised infix expression to a postfix expression
*/

char* infix_to_postfix(char *str) {
    /*
        Input:  A fully parenthesised infix expression
        Output: The postfix expression as a string
        Steps:
            1. Tokenise str to get a token array (say ta)
            2. Declare and initialise an operator stack (say opStack)
            3. Declare a string to store the postfix expression
            4. Linearly process ta till you hit a token of type EoS
                a) If the current token is an operand, append it to the postfix string
                b) If the current token is a parOpen, push '(' to opStack
                c) If the current token is an operator:
                    - Pop from opStack and append to postfix string while the top of the stack has higher or equal precedence
                    - Push the current operator to opStack
                d) If the current token is a parClose, pop from opStack and append to postfix string until '(' is encountered
            5. When the current token is EoS, pop all remaining operators from opStack and append to postfix string
        Error response: Print the following error messages to stderr and return NULL
            1. Tokenise error:  "Error: Could not tokenise <str>. Returning NULL.\n"
            2. Evaluation error: "Error; Invalid infix expression\n"
    */
    // Tokenise the input string
    Token* ta = tokenise(str);
    if (ta == NULL) {
        fprintf(stderr, "Error: Could not tokenise %s. Returning NULL.\n", str);
        return NULL;
    }

    // Initialize operator stack
    iStack opStack;
    init_is(&opStack, 100); // Assuming a maximum capacity of 100 for the stack

    // Initialize postfix string
    char* postfix = (char*)malloc(1000 * sizeof(char)); // Assuming a maximum length of 1000 for the postfix expression
    int postfix_index = 0;
    
  //Task 2: Solution

 
    int index = 0;
    while(ta[index].type != EoS){
        if(ta[index].type == operand){

            char buffer[100];
            sprintf(buffer, "%d ", ta[index].value);

            strcat(postfix, buffer);


        }
        else if(ta[index].type == operator || ta[index].type == parOpen){
            push_is(&opStack, ta[index].op);
        }

        else if(ta[index].type == parClose){

            char op[2];
            op[0] = pop_is(&opStack);
            op[1] = '\0';
            strcat(postfix, op);
            
            strcat(postfix, " ");
            if(pop_is(&opStack) != '(')return NULL;
        }

        index++;
    }



    if(!isempty_is(&opStack))return NULL;

    free_is(&opStack);
    // postfix[strlen(postfix) - 1] = '\0';
    return postfix;
}

/* Task 3. Evaluate a given postfix expression
*/

int postfix_eval(char *str) {
/*
	Input: 	A postfix expression
	Output: The result of evaluating the expression
	Steps:
		1.	Tokenise str to get a token array (say ta)
		2.	Declare and initialise an operand stack (say valStack) of required size
			(num of operand tokens in ta is one way to estimate the size)
		3.	Linearly process ta till you hit a token of type EoS
			a) 	If the current token is an operand, push the value to valStack
			b) 	If the current token is the unary negation
				-	pop valStack, 
				-	negate the popped value, and 
				-	push the result back to valStack
			b) 	If the current token is a binary operator
				-	pop valStack twice to get val2 and val1 (in that order)
				-	compute the result = val1 operator val2 using a switch case
					on the operator, and
				-	push the result back to valStack
		4.	When the current token is EoS, the final result can be popped from
			the valStack.
	Error repsonse:	 Print the following error messages to stderr and return INT_MIN
		1. Tokenise error:  "Error: Could not tokenise <str>. Returning <INT_MIN>.\n"
		2. Evalution error: "Error; Invalid postfix expression\n"
*/
	Token*	ta = tokenise(str);
	if(ta == NULL){
		fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
		return INT_MIN;
	}

	int numVals = 0, i = 0;
	while(ta[i].type != EoS){
		if(ta[i].type == operand){
			numVals++;
		}
		i++;
	}
		
	iStack valStack;
	init_is(&valStack, numVals);
	
	//Task 3: Solution
    int result ;
	
    //here i have to write my answer 
    int index = 0;
    while(ta[index].type != EoS){
        if(ta[index].type == operator){
            int result ;
            // printf("Operator %c\n", ta[index].op);
            if(ta[index].op == '~'){
                int val1 =  pop_is(&valStack);
                if(val1 == INT_MIN)return INT_MIN;
                result = -1 *val1;
                push_is(&valStack, result);

            }
            if(ta[index].op == '+'){
                int val1 = pop_is(&valStack);
                int val2 = pop_is(&valStack);
                if( val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;
                result = val1 + val2;
                // printf("rsult %d\n", result);
                push_is(&valStack, result);

            }if(ta[index].op == '-'){
                int val1 = pop_is(&valStack);
                int val2 = pop_is(&valStack);
                if( val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;
                result = - val1 + val2;
                push_is(&valStack, result);

            }if(ta[index].op == '/'){
                int val1 = pop_is(&valStack);
                int val2 = pop_is(&valStack);
                if( val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;
                result =  val2 / val1;
                push_is(&valStack, result);

            }if(ta[index].op == '*'){
                int val1 = pop_is(&valStack);
                int val2 = pop_is(&valStack);
                if( val1 == INT_MIN || val2 == INT_MIN)return INT_MIN;
                result = val1 * val2;
                push_is(&valStack, result);

            }
        }
        if(ta[index].type == operand){
            push_is(&valStack, ta[index].value);
            // printf("val %d\n", ta[index].value);
        }
        index++;
    }
    
    result = pop_is(&valStack);
    
    if(result == INT_MIN) {
		fprintf(stderr, "Error in postfix_eval: Invalid postfix expression\n");
		return INT_MIN;
	}

	// Check if valStack has been completely processed 
	// Otherwise the postfix expression is invalid




	if(!isempty_is(&valStack)) {
		fprintf(stderr, "Error in postfix_eval: Invalid postfix expression\n");
		return INT_MIN;
	}

	free_is(&valStack);
	return result;
}



/* Task 4. Generate an expression tree from a given postfix expression */
eTree* postfix_to_etree(char *str) {
/*
    Input:     A postfix expression
    Output: Pointer to the root of the equivalent expression tree.
    Steps:
        1.    Tokenise str to get a token array (say ta)
        2.    Declare and initialise a Node Stack (say nodeStack)
            (num of operand tokens in ta is one way to estimate the size)
        3.    Linearly process ta till you hit a token of type EoS
            a)     If the current token is an operand
                -    Create a new operand node with
                    -     current token as node token
                    -     NULL as left and NULL as right pointers
                    -    push this node to nodeStack
            b)     If the current token is the unary negation
                -    pop nodeStack once to get a single node t,
                    (return INT_MIN the token scan if you get NULL in this pop)
                -    Create a new operator node with
                    ~     current token as the node token
                    -    the popped node  t as its right child
                    -    NULL as its left child
                -    push this new node to nodeStack
            b)     If the current token is a binary operator
                -    pop nodeStack twice to get two nodes n2 and n1 (in that order)
                    (return INT_MIN the token scan if you get NULL in either pop)
                -    Create a new operator node token with
                    ~     current token as the node token
                    -    the popped node  n1 as its left child
                    -    the popped token  n2 as its right child
                -    push this new node to ns
        4.    When the current token is EoS, nodeStack contains only the root node
            of the expression tree
        5.    If either the current token is not EoS or result is INT_MIN or
            the valStack is not empty after the last pop, the expression was
            invalid. Print an error and return INT_MIN.

    Error response:     Print the following error messages to stderr and return NULL
        1. Tokenise error:  "Error: Could not tokenise <str>. Returning <INT_MIN>.\n"
        2. Evaluation error: "Error; Invalid postfix expression\n"
*/

    Token*    ta = tokenise(str);
    if(ta == NULL){
        fprintf(stderr, "Error: Could not tokenise %s. Returning %d.\n", str, INT_MIN);
        return NULL;
    }

    int numVals = 0, i = 0;
    while(ta[i].type != EoS){
        if(ta[i].type == operand){
            numVals++;
        }
        i++;
    }
        
    pStack nodeStack;
    init_ps(&nodeStack, numVals);
    
    eTree *node1, *node2;

    // Task 4. Solution

    while(ta->type != EoS){
        if(ta->type == operand){
            eTree* new = create_node(*ta, NULL, NULL);
            push_ps(&nodeStack, new);
            // printf("ta -> value %d\n",ta -> value);

        }
        else if(ta -> type == operator){
            if(ta -> op == '-' || ta -> op == '+' || ta -> op == '/' || ta -> op == '*'){
                // printf("ta -> op %c\n",ta -> op);

                node2 = pop_ps(&nodeStack);
                node1 = pop_ps(&nodeStack);
                if(node1 == NULL || node2 == NULL)return INT_MIN;
                eTree* new = create_node(*ta,node1, node2);
                push_ps(&nodeStack, new);
            }
            else if(ta -> op == '~'){
                node1 = NULL;
              
                node2 = pop_ps(&nodeStack);
                printf("ta -> op %c\n",ta -> op);
              
                if(node2 == NULL)return INT_MIN;
                eTree* new = create_node(*ta,node1, node2);
                push_ps(&nodeStack, new);

            }
        }
        ta++;
    }
    eTree*node = pop_ps(&nodeStack);
    
    free_ps(&nodeStack);

    return node;  // You may want to edit this
}




/* Task 5. Evaluate a given expression tree
*/
int etree_eval(eTree *t) {
/*     Input:    The root of an expression tree
    Action: Evaluate the expression tree recursively and return the answer
*/
    if (t == NULL) {
        fprintf(stderr, "Error in etree_eval: Trying to evaluate an empty tree\n");
        return INT_MIN;
    }
    if(t -> left == NULL && t -> right == NULL)return t -> token.value;

    int result ;
    // Task 5. Solution
    //here i have to evaluate the expression of this tree 
   
    if(t -> token.op == '~'){
        int right_eval = etree_eval(t -> right);
        result = -1 * right_eval;
        return result;
    }

   
   
    int left_eval = etree_eval(t -> left);
    int right_eval = etree_eval(t -> right);
    if( left_eval == INT_MIN || right_eval == INT_MIN)return INT_MIN;
    if(t -> token.op == '+')result = left_eval + right_eval;
    if(t -> token.op == '-')result =left_eval - right_eval;
    if(t -> token.op == '*')result = left_eval * right_eval;
    if(t -> token.op == '/')result = left_eval / right_eval;

    return result;
}

/* Task 6. Genrate a fully parenthesised infix expression from a given expression tree
*/

void etree_to_infix(eTree *t) {
/*     Input:    The root of an expression tree
    Action: Print the fully parenthesised infix expression of this tree
            Single operands should not be in parenthesis
*/
    if (t == NULL)
        return;
        
    // Task 6 . Solution
    etree_to_infix(t ->left);
    if(t -> token.type == operand)printf("%d " , t->token.value);
    if(t -> token.type == operator)printf("%c " , t->token.op);
    etree_to_infix(t -> right);
}   
int main(){
Token *ta;

	// Testing postfix_eval()
	printf("\nTesting Tasks 1 to 6.\n");
	printf("=======================\n");

	int nTests = 7;
	char infix[][100] = {
		"(2+31)",					// 33	
		"(2+(~31))", 				//-29
		"(10/(~(2+3)))", 			// ~2
		"((2+(3*1))-9)", 			// -4
		"(((2-3)+4)*(5+(6*7)))",	// 141
		"(((1+2-3)+4)*(5+(6*7)))",	// Invalid
		"(((2-3))+4)*(5+(6*7)))",	// Invalid
	};

	int result, result2;
	eTree *root;
	for(int i = 0; i < nTests; i++) {
		char* s = infix[i];
		// Task 1 Test
		printf("\n%d. Processing \"%s\"\n", i, s);
		printf("-----------------------------\n");
		result = infix_eval(s);
		printf("Task 1: Evaluate infix expression: Result = %d\n", result);
        if (result == INT_MIN)
        {
            continue;
        }
        
        // Task 2: Infix to Postfix Conversion
        char* postfix = infix_to_postfix(s);
        if (postfix != NULL) 
        {
            printf("Task 2: Infix to Postfix: %s\n", postfix);
        } else 
        {
            printf("Task 2: Infix to Postfix: Error\n");
            continue;
        }
		// Task 3 Test
		result2 = postfix_eval(postfix);
		printf("Task 3: Evaluate postfix expression: Result = %d\n", result2);

		root = postfix_to_etree(postfix);
		if(root == NULL){
			printf("Task 4: Invalid postfix expression\n");
            continue;

		}
		else {
			printf("Task 4: Expression Tree\n", 
				root->token.value, root->token.op);
			print_etree(root);
		}

		result = etree_eval(root);
		printf("Task 5: Evaluate expression tree: Result =%d\n", result );


        printf("Task 6: Fully parenthesised infix expression: ");
		etree_to_infix(root);
		printf("\n");
    }
}

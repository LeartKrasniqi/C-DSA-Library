/* Header for Stack */
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "list.h"


/* Implement a stack as a linked list */
typedef List Stack;




/* 
*********************************
        Interface Methods
*********************************
 */

/* Initialize a stack -- Uses list initialization implementation
	@param stack  	The allocated Stack structure
    @param destroy 	Pointer to function that will be used for deallocation
	
	Notes: 
	  - Must call this function before stack can be used
	  - If stack contains data that should not be freed, set destroy to NULL
	  - Complexity: O(1) 
*/
void stack_init(Stack *stack, void (*destroy)(void *data));


/* Destroy a stack -- Uses list destruction implementation
	@param stack  The stack to be destroyed

	Notes:
	  - Calls the function passed as destroy to stack_init() once for each element
	  - Complexity: O(n)
*/
void stack_destroy(Stack *stack);


/* Push an element onto the stack -- Uses list insertion implementation
	@param stack  The Stack structure
	@param data   The data associated with the element to be added to the stack

	@return 0 if pushing element was successful, -1 otherwise

	Notes:
	  - It is the responsibility of the caller to manage the storage associated with data
	  - Complexity: O(1)
*/
int stack_push(Stack *stack, const void *data);


/* Pop an element from the stack -- Uses list removal implementation
	@param stack  The Stack structure
	@param data   The data associated with the popped element

	@return 0 if successful, -1 otherwise

	Notes:
	  - Upon return, data points to the data stored in the popped element
	  - It is the responsibility of the caller to deal with the storage associated with the data
	  - Complexity: O(1)
*/
int stack_pop(Stack *stack, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get data stored in top element, or NULL if stack is empty */
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)

/* Number of elements in the stack -- Uses list size implementation */
#define stack_size list_size

#endif
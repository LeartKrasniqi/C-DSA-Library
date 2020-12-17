/* Implementation for Stack */
#include <stdlib.h>

#include "list.h"
#include "stack.h"


/* Initialize a stack */
void stack_init(Stack *stack, void (*destroy)(void *data))
{
    /* Use list initialization to implement stack as a linked list */
    list_init(stack, destroy);
}


/* Destroy a stack */
void stack_destroy(Stack *stack)
{
    /* Use list destruction since the stack is just a linked list */
    list_destroy(stack);
}


/* Push data onto the stack */
int stack_push(Stack *stack, const void *data)
{
    /* Use list insertion to insert the data at the head of the list (i.e., top of the stack) */
    return list_insert_next(stack, NULL, data);
}


/* Pop data from the stack */
int stack_pop(Stack *stack, void **data)
{
    /* Use list removal to remove the data at the head of the list (i.e., top of the stack) */
    return list_remove_next(stack, NULL, data);
}

/* Test of Stack Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void print_stack(Stack *s);

typedef struct Function_ {
    int addr;
    char *name;
} Function;

/* Test methods and macros
    Methods:
      - stack_init()
      - stack_destroy()
      - stack_push()
      - stack_pop()
    Macros:
      - stack_peek()
      - stack_size()

    Notes:
      - Stacks are implemented as linked lists
      - All linked list operations are also available for stacks
*/
int main()
{
    /* Allocate memory for a call stack */
    Stack *s = malloc(sizeof(*s));
    if(s == NULL)
        return -1;

    /* Initialize the stack with free() as its destroy function */
    stack_init(s, free);

    /* Create some functions to be pushed onto the stack */
    Function *f0 = malloc(sizeof(*f0));  f0->addr = 0x45;  f0->name = "main";
    Function *f1 = malloc(sizeof(*f1));  f1->addr = 0x100;  f1->name = "foo";
    Function *f2 = malloc(sizeof(*f2));  f2->addr = 0x00; f2->name = "impossible";

    /* Push onto the stack */
    printf("---Pushing functions onto stack ---\n");
    stack_push(s, f2);  printf("Pushed (name = '%s', addr = 0x%x) \n", f2->name, f2->addr);
    stack_push(s, f1);  printf("Pushed (name = '%s', addr = 0x%x) \n", f1->name, f1->addr);
    stack_push(s, f0);  printf("Pushed (name = '%s', addr = 0x%x) \n", f0->name, f0->addr);
    print_stack(s);
    printf("\n");

    /* Pop a function */
    Function *data;
    stack_pop(s, (void **)&data);
    printf("--- Popped a function ---\n");
    printf("Popped Function: (name = '%s', addr = 0x%x) \n", data->name, data->addr);
    print_stack(s);
    printf("\n");

    /* Peeking at data */
    data = (Function *)stack_peek(s);
    printf("--- Peeking at top of stack ---\n");
    printf("Peeked Function: (name = '%s', addr = 0x%x) \n", data->name, data->addr);
    print_stack(s);
    printf("\n");

    /* Destroy the stack */
    stack_destroy(s);

    return 0;
}

void print_stack(Stack *s)
{
    printf("Size: %d, Contents: ", stack_size(s));
    for(ListElement *e = list_head(s); e != NULL; e = list_next(e))
    {
        Function *data = (Function *)list_data(e);
        printf("(name = '%s', addr = 0x%x)  ", data->name, data->addr);
    }
    printf("\n");
}

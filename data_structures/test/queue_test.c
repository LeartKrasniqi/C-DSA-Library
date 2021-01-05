/* Test of Queue Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void print_queue(Queue *q);

typedef struct Function_ {
    int addr;
    char *name;
} Function;

/* Test methods and macros
    Methods:
      - queue_init()
      - queue_destroy()
      - queue_push()
      - queue_pop()
    Macros:
      - queue_peek()
      - queue_size()

    Notes:
      - Queues are implemented as linked lists
      - All linked list operations are also available for queues
*/
int main()
{
    /* Allocate memory for a call queue */
    Queue *q = malloc(sizeof(*q));
    if(q == NULL)
        return -1;

    /* Initialize the queue with free() as its destroy function */
    queue_init(q, free);

    /* Create some functions to be pushed onto the queue */
    Function *f0 = malloc(sizeof(*f0));  f0->addr = 0x45;  f0->name = "main";
    Function *f1 = malloc(sizeof(*f1));  f1->addr = 0x100;  f1->name = "foo";
    Function *f2 = malloc(sizeof(*f2));  f2->addr = 0x00; f2->name = "impossible";

    /* Push onto the queue */
    printf("--- Pushing functions onto queue ---\n");
    queue_push(q, f2);  printf("Pushed (name = '%s', addr = 0x%x) \n", f2->name, f2->addr);
    queue_push(q, f1);  printf("Pushed (name = '%s', addr = 0x%x) \n", f1->name, f1->addr);
    queue_push(q, f0);  printf("Pushed (name = '%s', addr = 0x%x) \n", f0->name, f0->addr);
    print_queue(q);
    printf("\n");

    /* Pop a function */
    Function *data;
    queue_pop(q, (void **)&data);
    printf("--- Popped a function ---\n");
    printf("Popped Function: (name = '%s', addr = 0x%x) \n", data->name, data->addr);
    print_queue(q);
    printf("\n");

    /* Peeking at data */
    data = (Function *)queue_peek(q);
    printf("--- Peeking at top of queue ---\n");
    printf("Peeked Function: (name = '%s', addr = 0x%x) \n", data->name, data->addr);
    print_queue(q);
    printf("\n");

    /* Destroy the queue */
    queue_destroy(q);

    return 0;
}

void print_queue(Queue *q)
{
    printf("Size: %d, Contents: ", queue_size(q));
    for(ListElement *e = list_head(q); e != NULL; e = list_next(e))
    {
        Function *data = (Function *)list_data(e);
        printf("(name = '%s', addr = 0x%x)  ", data->name, data->addr);
    }
    printf("\n");
}

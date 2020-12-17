/* Implementation for Queue */
#include <stdlib.h>

#include "list.h"
#include "queue.h"


/* Initialize a queue */
void queue_init(Queue *queue, void (*destroy)(void *data))
{
    /* Use list initialization to implement queue as a linked list */
    list_init(queue, destroy);
}


/* Destroy a queue */
void queue_destroy(Queue *queue)
{
    /* Use list destruction since the queue is just a linked list */
    list_destroy(queue);
}


/* Push data onto the queue */
int queue_push(Queue *queue, const void *data)
{
    /* Use list insertion to insert the data at the tail of the list (i.e., end of the queue) */
    return list_insert_next(queue, list_tail(queue), data);
}


/* Pop data from the queue */
int queue_pop(Queue *queue, void **data)
{
    /* Use list removal to remove the data at the head of the list (i.e., front of the queue) */
    return list_remove_next(queue, NULL, data);
}

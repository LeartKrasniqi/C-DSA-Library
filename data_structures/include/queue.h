/* Header for Queue */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "list.h"


/* Implement a queue as a linked list */
typedef List Queue;




/* 
*********************************
        Interface Methods
*********************************
 */

/* Initialize a queue -- Uses list initialization implementation
    @param queue    The allocated Queue structure
    @param destroy  Pointer to function that will be used for deallocation
    
    Notes: 
      - Must call this function before queue can be used
      - If queue contains data that should not be freed, set destroy to NULL
      - Complexity: O(1) 
*/
void queue_init(Queue *queue, void (*destroy)(void *data));


/* Destroy a queue -- Uses list destruction implementation
    @param queue  The queue to be destroyed

    Notes:
      - Calls the function passed as destroy to queue_init() once for each element
      - Complexity: O(n)
*/
void queue_destroy(Queue *queue);


/* Push an element onto the queue -- Uses list insertion implementation
    @param queue  The Queue structure
    @param data   The data associated with the element to be added to the queue

    @return 0 if pushing element was successful, -1 otherwise

    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int queue_push(Queue *queue, const void *data);


/* Pop an element from the queue -- Uses list removal implementation
    @param queue  The Queue structure
    @param data   The data associated with the popped element

    @return 0 if successful, -1 otherwise

    Notes:
      - Upon return, data points to the data stored in the popped element
      - It is the responsibility of the caller to deal with the storage associated with the data
      - Complexity: O(1)
*/
int queue_pop(Queue *queue, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get data stored in top element, or NULL if queue is empty */
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

/* Number of elements in the queue -- Uses list size implementation */
#define queue_size list_size

#endif

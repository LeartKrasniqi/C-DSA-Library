/* Header for Priority Queues */
#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

/* Implement priority queues as heaps */
typedef Heap PQueue;

/* Notes:
     - Operations of priority queues are identical to those of heaps, so we just define each pqueue operation to its heap counterpart
     - Check heap.h for detailed info about each method
     - Check heap.c for method implementations
*/

/*
********************************************
        Interface Methods and Macros
********************************************
*/

/* Initialize a priority queue */
#define pqueue_init heap_init

/* Destroy a priority queue */
#define pqueue_destroy heap_destroy

/* Insert a node into a priority queue */
#define pqueue_insert heap_insert

/* Extract a node from a priority queue */
#define pqueue_extract heap_extract

/* Peek at the top node in a priority queue */
#define pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])

/* Get number of nodes in a priority queue */
#define pqueue_size heap_size

#endif

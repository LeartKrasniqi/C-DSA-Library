/* Header file for Heaps */
#ifndef HEAP_H
#define HEAP_H

/* Structure definition for heaps */
typedef struct Heap_ {
    int size;       /* Number of nodes */

    int (*compare)(const void *key1, const void *key2);     /* Function used to compare two keys */
    void (*destroy)(void *data);                            /* Function used for deallocation (e.g., free()) */

    void **tree;    /* Array of nodes */
} Heap;




/*
*********************************
        Interface Methods
*********************************
*/

/* Initialize a heap
    @param heap     The allocated Heap structure 
    @param compare  Function used to compare nodes
    @param destroy  Function used for deallocation

    Notes:
      - Must be called before other heap operations can be used
      - Top-heavy Heap: compare should return 1 if key1>key2, 0 if key1=key2, and -1 if key1<key2
      - Bottom-heavy Heap: compare should return -1 if key1>key2, 0 if key1=key2, and 1 if key1<key2
      - For structured data containing several dynamically allocated members, set destroy to a function that frees each member as well as the structure itself
      - If heap contains data that should not be freed, set destroy to NULL
      - Complexity: O(1)
*/
void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));


/* Destroy a heap
    @param heap  The allocated Heap structure to be destroyed

    Notes:
      - Calls the function passed as destroy to heap_init() once for each node
      - Complexity: O(n), where n is the number of nodes in the heap
*/
void heap_destroy(Heap *heap);


/* Insert a node into a heap
    @param heap  The allocated Heap structure
    @param data  The data associated with the node to be inserted

    @return 0 if insertion successful, -1 otherwise

    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(log n), where n is the number of nodes in the tree
*/
int heap_insert(Heap *heap, const void *data);


/* Extract the node at the top of a heap 
    @param heap  The allocated Heap structure
    @param data  The data associated with the extracted node

    @return 0 if extraction successful, -1 otherwise
    
    Notes:
      - Upon return, data points to the data stored in the extracted node
      - It is the responsibility of the caller to manage the storage associated with the data
      - Complexity: O(log n), where n is the number of nodes in the tree
*/
int heap_extract(Heap *heap, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get number of nodes in heap */
#define heap_size(heap) ((heap)->size)

#endif

/* Header for Doubly Linked List */
#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>


/*
********************************************
        Element and List Definitions
********************************************
*/

/* Structure definition for doubly linked list elements */
typedef struct DListElement_ {
    void *data;                     /* Data associated with element */
    struct DListElement_ *prev;     /* Previous element in list */
    struct DListElement_ *next;     /* Next element in list */
} DListElement;


/* Structure definition of doubly linked list */
typedef struct DList_ {
    int size;           /* Number of elements */
    
    int (*match)(const void *key1, const void *key2);   /* Not used by linked list, but by other derived types */
    void (*destroy)(void *data);                        /* Function that can be used for deallocation (e.g., free()) */
    
    DListElement *head;  /* First element */
    DListElement *tail;  /* Last element */
} DList;




/* 
*********************************
        Interface Methods
*********************************
 */

/* Initialize a doubly linked list
    @param list     The allocated DList structure
    @param destroy  Pointer to function that will be used for deallocation 

    Notes:
      - Must be called before DList operations can be used
      - If list contains data that should not be freed, set destroy to NULL
      - Complexity: O(1)
*/
void dlist_init(DList *list, void (*destroy)(void *data));


/* Destroy a doubly linked list
    @param list  The list to be destroyed

    Notes:
      - Calls the function passed as destroy to dlist_init() once for each element
      - Complexity: O(n)
*/
void dlist_destroy(DList *list);


/* Insert new element just after an existing element 
    @param list     The DList structure
    @param element  The existing element
    @param data     The data associated with the new element

    @return 0 if insertion successful, -1 otherwise

    Notes:
      - When inserting into an empty list, set element to NULL
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int dlist_insert_next(DList *list, DListElement *element, const void *data);


/* Insert new element just before an existing element
    @param list     The DList structure
    @param element  The existing element
    @param data     The data associated with the new element

    @return 0 if insertion successful, -1 otherwise

    Notes:
      - When inserting into an empty list, set element to NULL
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int dlist_insert_prev(Dlist *list, DListElement *element, const void *data);


/* Remove element from list 
    @param list     The DList structure
    @param element  The element to be removed
    @param data     The data associated with the element

    @return 0 if removal successful, -1 otherwise

    Notes:
      - Upon return, data points to the data stored in the element that was removed
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int dlist_remove(DList *list, DListElement *element, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Number of elements in the list */
#define dlist_size(list) ((list)->size)

/* Element at head of the list */
#define dlist_head(list) ((list)->head)

/* Check if element is head of the list */
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

/* Element at tail of the list */
#define dlist_tail(list) ((list)->tail)

/* Check if element is tail of the list */
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

/* Data stored in specified element */
#define dlist_data(element) ((element)->data)

/* Element just after specified element */
#define dlist_next(element) ((element)->next)

/* Element just before specified element */
#define dlist_prev(element) ((element)->prev)

#endif

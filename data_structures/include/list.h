/* Header for Linked List */
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>


/*
********************************************
        Element and List Definitions
********************************************
*/

/* Struct representing element of linked list */
typedef struct ListElement_ {
    void *data;                 /* Data member */				
    struct ListElement_ *next;  /* Next element in list */
} ListElement;


/* Struct representing linked list */
typedef struct List_ {
    int size;			/* Number of elements */
	
    int (*match)(const void *key1, const void *key2);	/* Not used by linked list, but by other derived types */
    void (*destroy)(void *data);						/* Function that can be used for deallocation (e.g., free()) */
	
    ListElement *head;  /* First element */
    ListElement *tail;  /* Last element */
} List;




/* 
*********************************
        Interface Methods
*********************************
 */

/* Initialize a linked list
    @param list  	The allocated list structure
    @param destroy 	Pointer to function that will be used for deallocation
	
	Notes: 
	  - Must call this function before list can be used
	  - If list contains data that should not be freed, set destroy to NULL
	  - Complexity: O(1) 
*/
void list_init(List *list, void (*destroy)(void *data));


/* Destroy a linked list
	@param list  The list to be destroyed

	Notes:
	  - Calls the function passed as destroy to list_init() once for each element
	  - Complexity: O(n)
*/
void list_destroy(List *list);


/* Insert a new element just after an existing element
	@param list     The list structure
	@param element  The existing element in the list
	@param data     The data associated with the new element
	
	@return 0 if insertion successful, -1 otherwise

	Notes:
	  - If element is NULL, the new element is inserted at the head of the list
	  - It is the responsibility of the caller to manage the storage associated with data
	  - Complexity: O(1)
*/ 
int list_insert_next(List *list, ListElement *element, const void *data);


/* Remove an element just after an existing element
	@param list     The list structure
	@param element  The existing element
	@param data     The data associated with the removed element

	@return 0 if removal successful, -1 otherwise

	Notes:
	  - If element is NULL, the element at the head of the list is removed
	  - Upon return, data points to the data stored in the removed element
	  - It is the responsibility of the caller to deal with the storage associated with the data
	  - Complexity: O(1)
*/
int list_remove_next(List *list, ListElement *element, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Number of elements in list */
#define list_size(list) ((list)->size)

/* Element at head of the list */
#define list_head(list) ((list)->head)

/* Check if element is head of list */
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

/* Element at tail of list */
#define list_tail(list) ((list)->tail)

/* Check if element is tail of list */
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

/* Data stored in the specified element */
#define list_data(element) ((element)->data)

/* Element following specified element */
#define list_next(element) ((element)->next)

#endif

/* Header for Circular List */
#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

/* Structure definition for Circular List element */
typedef struct CListElement_ {
	void *data;						/* Data associated with element */ 
	struct CListElement_ *next;		/* Pointer to next element in list */
} CListElement;


/* Structure definition for Circular List */
typedef struct CList_ {
	int size;			/* Number of elements */
	
    int (*match)(const void *key1, const void *key2);	/* Not used by circular list, but by other derived types */
    void (*destroy)(void *data);						/* Function that can be used for deallocation (e.g., free()) */

	CListElement *head;		/* First element */
} CList;




/* 
*********************************
        Interface Methods
*********************************
 */

/* Initialize a circular list 
	@param list     The allocated CList structure
	@param destroy  Pointer to function that will be used for deallocation 

	Notes:
	  - Must be called before CList operations can be used
	  - If list contains data that should not be freed, set destroy to NULL
	  - Complexity: O(1)
*/
void clist_init(CList *list, void (*destroy)(void *data));


/* Destroy a circular list
	@param list  The list to be destroyed

	Notes:
	  - Calls the function passed as destroy to clist_init() once for each element
	  - Complexity: O(n)
*/
void clist_destroy(CList *list);


/* Insert new element just after an existing element 
	@param list     The CList structure
	@param element  The existing element
	@param data     The data associated with the new element

	@return 0 if insertion successful, -1 otherwise

	Notes:
	  - When inserting into an empty list, set element to NULL
	  - It is the responsibility of the caller to manage the storage associated with data
	  - Complexity: O(1)
*/
int clist_insert_next(CList *list, CListElement *element, const void *data);


/* Remove an element just after an existing element
	@param list     The CList structure
	@param element  The existing element
	@param data     The data associated with the removed element

	@return 0 if removal successful, -1 otherwise

	Notes:
	  - Upon return, data points to the data stored in the removed element
	  - It is the responsibility of the caller to deal with the storage associated with the data
	  - Complexity: O(1)
*/
int clist_remove_next(CList *list, CListElement *element, void **data);




/*
*****************************
        Useful Macros        
*****************************
*/

/* Get number of elements in list */
#define clist_size(list) ((list)->size)

/* Get first element of list */
#define clist_head(list) ((list)->head)

/* Get data associated with specified element */
#define clist_data(element) ((element)->data)

/* Get element right after specified element */
#define clist_next(element) ((element)->next)

#endif
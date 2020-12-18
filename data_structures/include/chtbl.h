/* Header file for Chained Hash Table */
#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

/* Definition of structure representing chained hash table */
typedef struct CHTbl_ {
    int buckets;        /* Number of buckets (i.e., lists where each element key has same hash value) */

    int (*h)(const void *key);                          /* Hash function */
    int (*match)(const void *key1, const void *key2);   /* Function to see if two keys match */
    void (*destroy)(void *data);                        /* Function used to deallocate data */

    int size;           /* Number of elements in the table */
    List *table;        /* The table itself -- Implemented as a linked list */
} CHTbl;




/*
*********************************
        Interface Methods
*********************************
*/

/* Initialize a chained hash table 
    @param htbl     The allocated CHTbl struct
    @param buckets  Number of buckets in the hash table
    @param h        Pointer to hash function
    @param match    Pointer to function used for matching keys
    @param destroy  Pointer to function used for deallocation

    @return 0 if initialization successful, -1 otherwise

    Notes:
      - Must be called before CHTbl operations can be used
      - If hash table contains data that should not be freed, set destroy to NULL
      - Complexity: O(n), where n is the number of buckets
*/
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));


/* Destroy a chained hash table
    @param htbl  The hash table to be destroyed

    Notes:
      - Calls the function passed as detroy to chtbl_init() once for each element
      - Complexity: O(n), where n is the number of buckets
*/
void chtbl_destroy(CHTbl *htbl);


/* Insert an element into a chained hash table
    @param htbl  The CHTbl structure
    @param data  The data associated with the element to be inserted

    @return 0 if successful, 1 if element already exists, -1 otherwise 

    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int chtbl_insert(CHTbl *htbl, const void *data);


/* Remove an element from a chained hash table
    @param htbl  The CHTbl structure
    @param data  The data associated with the element to be removed

    @return 0 if successful, -1 otherwise

    Notes:
      - Removes the element with data member matching data
      - Upon return, data points to the data stored in the element that was removed
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int chtbl_remove(CHTbl *htbl, void **data);


/* Determine whether an element exists in a chained hash table
    @param htbl  The CHTbl structure
    @param data  The data associated with the element

    @return 0 if the element is found, -1 otherwise

    Notes:
      - If a match is found, data points to the matching data in the hash table upon return
      - Complexity: O(1)
*/
int chtbl_lookup(const CHTbl *htbl, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get number of elements in hash table */
#define chtbl_size(htbl) ((htbl)->size)

#endif

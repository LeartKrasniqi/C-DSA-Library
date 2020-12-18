/* Header file for Open-Addressed Hash Table */
#ifndef OHTBL_H
#define OHTBL_H

#include <stdlib.h>


/* Definition of structure representing open-addressed hash table */
typedef struct OHTbl_ {
    int positions;  /* Number of positions allocated in the hash table -- Ideally a prime number */
    void *vacated;  /* Pointer which will be initalized to a storage location to indicate a position in the table has had an element removed */

    int (*h1)(const void *key);                         /* First hash function */
    int (*h2)(const void *key);                         /* Second hash function (for double hashing) -- Ideally returns a positive integer less than positions */
    int (*match)(const void *key1, const void *key2);   /* Function to see if two keys match */
    void (*destroy)(void *data);                        /* Function used to deallocate data */

    int size;           /* Number of elements in the table */
    void **table;       /* The table itself */
} OHTbl;




/*
*********************************
        Interface Methods
*********************************
*/

/* Initialize an open-addressed hash table 
    @param htbl       The allocated OHTbl struct
    @param positions  Number of positions in the hash table
    @param h1         Pointer to the first hash function
    @param h2         Pointer to the second hash function (for double hashing)
    @param match      Pointer to function used for matching keys
    @param destroy    Pointer to function used for deallocation

    @return 0 if initialization successful, -1 otherwise

    Notes:
      - Must be called before OHTbl operations can be used
      - If hash table contains data that should not be freed, set destroy to NULL
      - Complexity: O(n), where n is the number of poisitions
*/
int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int (*h2)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));


/* Destroy an open-addressed hash table
    @param htbl  The hash table to be destroyed

    Notes:
      - Calls the function passed as detroy to ohtbl_init() once for each element
      - Complexity: O(n), where n is the number of buckets
*/
void ohtbl_destroy(OHTbl *htbl);


/* Insert an element into an open-addressed hash table
    @param htbl  The OHTbl structure
    @param data  The data associated with the element to be inserted

    @return 0 if successful, 1 if element already exists, -1 otherwise 

    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int ohtbl_insert(OHTbl *htbl, const void *data);


/* Remove an element from an open-addressed hash table
    @param htbl  The OHTbl structure
    @param data  The data associated with the element to be removed

    @return 0 if successful, -1 otherwise

    Notes:
      - Removes the element with data member matching data
      - Upon return, data points to the data stored in the element that was removed
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int ohtbl_remove(OHTbl *htbl, void **data);


/* Determine whether an element exists in an open-addressed hash table
    @param htbl  The OHTbl structure
    @param data  The data associated with the element

    @return 0 if the element is found, -1 otherwise

    Notes:
      - If a match is found, data points to the matching data in the hash table upon return
      - Complexity: O(1)
*/
int ohtbl_lookup(const OHTbl *htbl, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get number of elements in hash table */
#define ohtbl_size(htbl) ((htbl)->size)

#endif

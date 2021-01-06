/* Header for Sets */
#ifndef SET_H
#define SET_H

#include <stdlib.h>

#include "list.h"

/* Implement a set as a linked list */
typedef List Set;



/*
*********************************
        Interface Methods       
*********************************
*/

/* Initialize a set 
    @param set      The allocated Set struct
    @param match    Pointer to function used to determine if two members match (return 1 if match, 0 otherwise)
    @param destroy  Pointer to function used for deallocation 

    Notes:
      - Must be called before Set operations can be used
      - If set contains data that should not be freed, set destroy to NULL
      - Complexity: O(1)
*/
void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));


/* Destroy a set 
    @param set  The set to be destroyed

    Notes:
      - Calls the function passed as destroy to set_init() once for each element
      - Complexity: O(n)
*/
void set_destroy(Set *set);


/* Insert new element into the set
    @param set   The Set structure
    @param data  The data associated with the new element

    @return 0 if successful, -1 otherwise

    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(n)
*/
int set_insert(Set *set, const void *data);


/* Remove an element from the set
    @param set   The Set structure
    @param data  The data associated with the element

    @return 0 if successful, -1 otherwise

    Notes:
      - Removes the element with data member matching data
      - Upon return, data points to the data stored in the element that was removed
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(n)
*/
int set_remove(Set *set, void **data);


/* Compute the union of two sets
    @param setu  The set containing the union of the two sets
    @param set1  The first set
    @param set2  The second set

    @return 0 if successful, -1 otherwise
    
    Notes:
      - This function calls set_init() for setu
      - setu data member points to data in set1 and set2
      - Data in set1 and set2 must remain valid until setu is destroyed
      - Complexity: O(mn), where m,n = # of elements in set1,set2
*/
int set_union(Set *setu, const Set *set1, const Set *set2);


/* Compute the insersection of two sets
    @param seti  The set containing the insersection of the two sets
    @param set1  The first set
    @param set2  The second set

    @return 0 if succssful, -1 otherwise

    Notes:
      - This function calls set_init() for seti 
      - seti data member points to data in set1
      - Data in set1 must remain valid until seti is destroyed
      - Complexity: O(mn), where m,n = # of elements in set1,set2
*/
int set_intersection(Set *seti, const Set *set1, const Set *set2);


/* Compute the difference of two sets
    @param setd  The set containing the difference of the two sets
    @param set1  The first set
    @param set2  The second set

    @return 0 if successful, -1 otherwise

    Notes:
      - Computes set1 - set2
      - This function calls set_init() for setd
      - setd data member points to data in set1
      - Data in set1 must remain valid until setd is destroyed
      - Complexity: O(mn), where m,n = # of elements in set1,set2
*/
int set_difference(Set *setd, const Set *set1, const Set *set2);


/* Determine whether element is part of the set
    @param set   The Set structure
    @param data  The data associated with the element

    @return 1 is the element is in the set, 0 otherwise

    Notes:
      - Checks if data matches any of the elements' data members 
      - Complexity: O(n)
*/ 
int set_is_element(const Set *set, const void *data);


/* Determine whether a set is a subset of another
    @param set1  The first set
    @param set2  The second set

    @return 1 if the set is a subset, 0 otherwise

    Notes:
      - Checks if set1 is a subset of set2
      - Complexity: O(mn), where m,n = # of elements in set1,set2
*/
int set_is_subset(const Set *set1, const Set *set2);


/* Determine whether two sets are equal
    @param set1  The first set
    @param set2  The second set

    @return 1 if the two sets are equal, 0 otherwise

    Notes:
      - Complexity: O(mn), where m,n = # of elements in set1,set2
*/
int set_is_equal(const Set *set1, const Set *set2);




/*
*****************************
        Useful Macros        
*****************************
*/

/* Get number of elements in set */
#define set_size(set)  ((set)->size)

#endif

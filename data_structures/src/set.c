/* Implementation of Sets */
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "set.h"

/* Initialize a set with a match function and a destroy function */
void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    /* Used linked list initialization since the set is just a linked list */
    list_init(set, destroy);
    set->match = match;
}


/* Destroy a set */
void set_destroy(Set *set)
{
    /* Call destroy method for linked lists */
    list_destroy(set);
}


/* Insert a new element into the set */
int set_insert(Set *set, const void *data)
{
    /* Only allow unique elements in the set */
    if(set_is_element(set, data))
        return -1;

    /* Insert element after the tail of the list representing the set */
    return list_insert_next(set, list_tail(set), data);
}


/* Remove an element from the set */
int set_remove(Set *set, void **data)
{
    ListElement *element;       /* Will hold the element we are trying to remove */   
    ListElement *prev = NULL;   /* Will hold the element right before the one we want to move */

    /* Find the element to remove by traversing from head to tail */
    for(element = list_head(set); element != NULL; element = list_next(element))
    {
        /* Call the user-provided match function to see if the data in the current element matches the provided data */
        if(set->match(*data, list_data(element)))
            break;
        
        /* If the data did not match, set prev to the current element */
        prev = element;
    }

    /* If the element was not found, return an error */
    if(element == NULL)
        return -1;

    /* Remove the element using list operations */
    return list_remove_next(set, prev, data);
}


/* Compute the union of two sets */
int set_union(Set *setu, Set *set1, Set *set2)
{
    /* Initialize the set for the union -- destroy is set to NULL because set1 and set2 control how they destroy their data */
    set_init(setu, set1->match, NULL);

    ListElement *element;   /* Will be used to hold the current element as we traverse the sets */
    void *data;             /* Will be used to hold the data associated with the current element */

    /* Insert the elements of the first set */
    for(element = list_head(set1); element != NULL; element = list_next(element))
    {
        /* Save the data associated with the element */
        data = list_data(element);

        /* Try to insert the element with the data at the tail of the new set and destroy/return error if unsuccessful */
        if(list_insert_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    /* Insert the elements of the second set */
    for(element = list_head(set2); element != NULL; element = list_next(element))
    {
        /* If the element is a member of set1, then we already inserted it so skip it */
        if(set_is_element(set1, list_data(element)))
            continue;
        
        /* Save the data associated with the element */
        data = list_data(element);

        /* Try to insert the element with the data at the tail of the new set and destroy/return error if unsuccessful */
        if(list_insert_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    /* If we get here, all insertions were successful so we return 0 */
    return 0;
}


/* Compute the intersection of two sets */
int set_intersection(Set *seti, Set *set1, Set *set2)
{
    /* Initialize the set for the intersection -- destroy is set to NULL because set1 controls how it destroys its data */
    set_init(seti, set1->match, NULL);

    ListElement *element;   /* Will be used to hold the current element as we traverse the sets */
    void *data;             /* Will be used to hold the data associated with the current element */

    /* Traverse the first set and insert elements also present in the second set */
    for(element = list_head(set1); element != NULL; element = list_next(element))
    {
        /* Check if element is also a member of set2 */
        if(set_is_element(set2, list_data(element)))
        {
            /* Save the data associated with the element */
            data = list_data(element);

            /* Try to insert the element with the data at the tail of the new set and destroy/return error if unsuccessful */
            if(list_insert_next(seti, list_tail(seti), data) != 0)
            {
                set_destroy(seti);
                return -1;
            }
        }
    }

    /* If we get here, all insertions were successful so we return 0 */
    return 0;
}


/* Compute the difference of two sets (set1 - set2) */
int set_difference(Set *setd, Set *set1, Set *set2)
{
    /* Initialize the set for the difference -- destroy is set to NULL because set1 controls how it destroys its data */
    set_init(setd, set1->match, NULL);

    ListElement *element;   /* Will be used to hold the current element as we traverse the sets */
    void *data;             /* Will be used to hold the data associated with the current element */

    /* Traverse the first set and inssert elements that are not present in the second set */
    for(element = list_head(set1); element != NULL; element = list_next(element))
    {
        /* Check if element is NOT a member of set2 */
        if(!set_is_element(set2, list_data(element)))
        {
            /* Save the data associated with the element */
            data = list_data(element);

            /* Try to insert the element with the data at the tail of the new set and destroy/return error if unsuccessful */
            if(list_insert_next(setd, list_tail(setd), data) != 0)
            {
                set_destroy(setd);
                return -1;
            }
        }
    }

    /* If we get here, all insertions were successful so we return 0 */
    return 0;
}


/* Determine whether element is part of the set */
int set_is_element(Set *set, const void *data)
{
    /* Will be used to hold the current element as we traverse the set */
    ListElement *element;

    /* Traverse the set and see if the data provided matches any elements' data */
    for(element = list_head(set); element != NULL; element = list_next(element))
    {
        /* Call a user defined match function to see if the data matches and return 1 if it does */
        if(set->match(data, list_data(element)))
            return 1;
    }

    /* If we get here, data did not match any of the element data members so we return 0 (i.e., no match) */
    return 0;
}


/* Determine whether set1 is a subset of set2 */
int set_is_subset(Set *set1, Set *set2)
{
    /* Quick test -- If set1 has more elements, it cannot be a subset */
    if(set_size(set1) > set_size(set2))
        return 0;

    /* Will be used to hold the current element as we traverse the set */
    ListElement *element;

    /* Traverse set1 and see if all its elements are in set2 */
    for(element = list_head(set1); element != NULL; element = list_next(element))
    {
       /* Check if element is NOT a member of set2 -- if so, return 0 (i.e., not a subset) */
       if(!set_is_element(set2, list_data(element)))
          return 0;
    }

   /* If we get here, all the elements in set1 were in set2 so return 1 */
   return 1;
}


/* Determine whether two sets are equal */
int set_is_equal(Set *set1, Set *set2)
{
    /* Quick test -- The sets must be the same size */
    if(set_size(set1) != set_size(set2))
        return 0;

    /* Sets of the same size are equal iff they are subsets */
    return set_is_subset(set1, set2);
}


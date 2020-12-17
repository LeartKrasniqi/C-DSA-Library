/* Implementation of Chained Hash Table */
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"

/* Initialize a chained hash table */
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    /* Allocate memory for hash table */
    htbl->table = malloc(buckets * sizeof(List));
    if(htbl->table == NULL)
        return -1;

    /* Initialize the buckets using list initialization */
    htbl->buckets = buckets;
    for(int i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    /* Set the member functions */
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;

    /* Initialize the number of elements in the hash table */
    htbl->size = 0;

    return 0;
}


/* Destroy a chained hash table */
void chtbl_destroy(CHTbl *htbl)
{
    /* Destroy each bucket in the table using list destruction */
    for(int i = 0; i < htbl->buckets; i++)
        list_destroy(&htbl->table[i]);

    /* Free the storage allocated for the hash table */
    free(htbl->table);

    /* To be safe, clear the structure */
    memset(htbl, 0, sizeof(CHTbl));
}


/* Insert an element into a chained hash table */
int chtbl_insert(CHTbl *htbl, const void *data)
{
    /* Quick check to see if data is already in the table */
    void *temp = (void *)data;
    if(chtbl_lookup(htbl, &temp) == 0)
        return 1;

    /* Hash the key */
    int bucket = htbl->h(data) % htbl->buckets;

    /* Insert the data into the proper bucket using list insertion */
    int retval = list_insert_next(&htbl->table[bucket], NULL, data);

    /* If insertion into the bucket was successful, update the size of the hash table */
    if(retval == 0)
        htbl->size += 1;

    return retval;
}


/* Remove an element from a chained hash table */
int chtbl_remove(CHTbl *htbl, void **data)
{
    /* Hash the key */
    int bucket = htbl->h(*data) % htbl->buckets;
    
    ListElement *element;       /* Will hold the current element in the bucket during list traversal */
    ListElement *prev = NULL;   /* Will hold the element prior to the current element in the bucket (to be used in list removal function) */

    /* Search for the data in the proper bucket by traversing the list from head to tail */
    for(element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element))
    {
        /* Check to see if current element in bucket matches the specified data */
        if(htbl->match(*data, list_data(element)))
        {

            /* Try to remove the data from the bucket using list removal */
            if(list_remove_next(&htbl->table[bucket], prev, data) == 0)
            {
                htbl->size -= 1;
                return 0;
            }
            /* If removal failed, return an error */
            else
                return -1;
        }

        /* If the element did not match, update the prev to the current element for the next iteration */
        prev = element;
    }

    /* If we get here, there were no matches so return an error */
    return -1;
}


/* Determine whether an element exists in a chained hash table */
int chtbl_lookup(const CHTbl *htbl, void **data)
{
    /* Hash the key */
    int bucket = hbtl->h(*data) % htbl->buckets;

    /* Search for the data in the proper bucket */
    ListElement *element;
    for(element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element))
    {
        /* Check if element has matching data */
        if(htbl->match(*data, list_data(element)))
        {
            /* data now points to the data from the table */
            *data = list_data(element);
            return 0;
        }
    }

    /* If we get here, there were no matches so return that data was not found */
    return -1;
}


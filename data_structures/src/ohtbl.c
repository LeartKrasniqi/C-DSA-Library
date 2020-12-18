/* Implementation of Open-Addressed Hash Table */
#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

/* Reserve a memory address for vacated elements */
static char vacated;


/* Initialize an open-addressed hash table */
int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int (*h2)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    /* Allocate memory for the hash table */
    htbl->table = malloc(positions * sizeof(void *));
    if(htbl->table == NULL)
        return -1;

    /* Initialize each position */
    htbl->positions = positions;
    for(int i = 0; i < htbl->positions; i++)
        htbl->table[i] = NULL;

    /* Set the vacated member to the memory address reserved for this */
    htbl->vacated = &vacated;

    /* Set the member functions */
    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destroy = destroy;

    /* Initialize the number of elements */
    htbl->size = 0;

    /* If we get here, initialization was successful */
    return 0;
}


/* Destroy an open-addressed hash table */
void ohtbl_destroy(OHTbl *htbl)
{
    /* If the user provided a destroy function, call it for each element in the table */
    if(htbl->destroy != NULL)
    {
        for(int i = 0; i < htbl->positions; i++)
        {
            /* Only destroy entries that actually exist in the table (i.e., only occupied positions) */
            if( (htbl->table[i] != NULL) && (htbl->table[i] != htbl->vacated) )
                htbl->destroy(htbl->table[i]);
        }
    }

    /* Free the storage allocated for the hash table */
    free(htbl->table);

    /* To be safe, clear the structure */
    memset(htbl, 0, sizeof(htbl));
}


/* Insert an element into an open-addressed hash table */
int ohtbl_insert(OHTbl *htbl, const void *data)
{
    /* Do not exceed total number of positions in table */
    if(ohtbl_size(htbl) == htbl->positions)
        return -1;

    /* Do nothing if the element already exists */
    void *temp = (void *)data;
    if(ohtbl_lookup(htbl, &temp) == )
        return 1;

    /* Loop through each position index and try double hashing to insert the new element */
    for(int i = 0; i < htbl->positions; i++)
    {
        /* Use double hashing to hash the key */
        int position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;

        /* If the position is NULL or marked as vacated, then it does not contain an element, so add the new element there */
        if( (htbl->table[position] == NULL) || (htbl->table[position] == htbl->vacated) )
        {
            htbl->table[position] = (void *)data;
            htbl->size += 1;
            return 0;
        }
    }

    /* If we get here, the hash functions were not chosen properly, so return an error */
    return -1;
}


/* Remove an element from an open-addressed hash table */
int ohtbl_remove(OHTbl *htbl, void **data)
{
    /* Loop through each position index and use double hashing to try to find the element and remove it */
    for(int i = 0; i < htbl->positions; i++)
    {
        /* Use double hashing to hash the key */
        int position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

        /* If the positions is NULL, there is nothing at that hash value so return error */
        if(htbl->table[position] == NULL)
            return -1;
        
        /* If the position is marked as vacated, search beyond it */
        if(htbl->table[position] == htbl->vacated)
            continue;

        /* If there is a match, pass back the data, mark the position as vacated, and update the size */
        if(htbl->match(htbl->table[position], *data))
        {
            *data = htbl->table[position];
            htbl->table[position] = htbl->vacated;
            htbl->size -= 1;
            return 0;
        }
    }

    /* If we get here, the data was not found so return an error */
    return -1;
}


/* Determine whether an element exists in an open-addressed hash table */
int ohtbl_lookup(const OHTbl *htbl, void **data)
{
    /* Loop through each position and use double hasing to try to find the element */
    for(int i = 0; i < htbl->positions; i++)
    {
        /* Use double hashing to hash the key */
        int position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

        /* If the positions is NULL, there is nothing at that hash value so return error */
        if(htbl->table[position] == NULL)
            return -1;

        /* If there is a match, pass back the data from the table */
        if(htbl->match(htbl->table[position], *data))
        {
            *data = htbl->table[position];
            return 0;
        }
    }

    /* If we get here, the data was not found so return an error */
    return -1;
}


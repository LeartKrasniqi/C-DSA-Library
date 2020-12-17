/* Implementation of Circular List */
#include <stdlib.h>
#include <string.h>

#include "clist.h"

/* Initialize a circular list */
void clist_init(CList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
}


/* Destroy a circular list */
void clist_destroy(CList *list)
{
    /* Will be used to hold the data associated with each element */
    void *data;

    /* Remove each element */
    while(clist_size(list) > 0)
    {
        /* Continuously remove the head element.  If the user supplied a destroy function, apply it to the data */
        if( (clist_remove_next(list, list->head, (void **)&data) == 0) && (list->destroy != NULL) )
            list->destroy(data);
    }

    /* To be safe, clear the structure */
    memset(list, 0, sizeof(CList));
}


/* Insert new element just after existing element */ 
int clist_insert_next(CList *list, CListElement *element, const void *data)
{
    /* Allocate memory for the new element */
    CListElement *new_element = malloc(sizeof(CListElement));
    if(new_element == NULL)
        return -1;

    /* Set the data member of new_element to the provided data */
    new_element->data = (void *)data;

    /* Handle insertion in an empty list */
    if(clist_size(list) == 0)
    {
        new_element->next = new_element;
        list->head = new_element;
    }
    /* Otherwise, handle insertion in a nonempty list */
    else
    {
        new_element->next = element->next;
        element->next = new_element;
    }

    /* Update the size of the list */
    list->size += 1;

    /* If we get here, we are successful so return 0 */
    return 0;
}


/* Remove an element just after an existing element */
int clist_remove_next(CList *list, CListElement *element, void **data)
{
    /* If trying to remove from empty list, return an error */
    if(clist_size(list) == 0)
        return -1;

    /* Will be used to hold the element to be removed */
    CListElement *old_element = element->next;

    /* data now points to the data associated with the element to be removed */
    *data = old_element->data;

    /* Handle removing from list with only one element */
    if(old_element == element)
        list->head = NULL;
    /* Otherwise, handle removing from list with more than one element */
    else
    {
        /* Set the next pointer of element to the element right after old_element (i.e., the element to be removed) */
        element->next = element->next->next;

        /* If the element to be removed was the head of the list, update the head */
        if(old_element == clist_head(list))
            list->head = old_element->next;
    }

    /* Free the storage allocated by the CListElement */
    free(old_element);

    /* Update the size of the list */
    list->size -= 1;

    /* If we get here, we are successful so return 0 */
    return 0;
}

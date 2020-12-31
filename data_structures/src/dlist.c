/* Implementation of Doubly Linked List */
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

/* Initialize a Doubly Linked List */
void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}


/* Destroy a Doubly Linked List */
void dlist_destroy(DList *list)
{
    /* Will hold the data associated with each element */
    void *data;

    /* Remove each element */
    while(dlist_size(list) > 0)
    {
        /* Continuously remove the tail element.  If the user supplied a destroy function, apply it to the data */
        if( (dlist_remove(list, dlist_tail(list), (void **)&data) == 0) && (list->destroy != NULL) )
            list->destroy(data);
    }

    /* To be safe, clear the structure */
    memset(list, 0, sizeof(DList));
}


/* Insert an element just after an existing element */
int dlist_insert_next(DList *list, DListElement *element, const void *data)
{
    /* If element is NULL and the list is not empty, return an error */
    if( (element == NULL) && (dlist_size(list) != 0) )
        return -1;

    /* The new element to be added */
    DListElement *new_element = malloc(sizeof(DListElement));
    if(new_element == NULL)
        return -1;

    /* Set data member to provided data */
    new_element->data = (void *)data;

    /* Handle insertion when list is empty */
    if(dlist_size(list) == 0)
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    /* Otherwise, handle insertion when list is nonempty */
    else
    {
        new_element->next = element->next;
        new_element->prev = element;

        /* If element was the tail, the new tail is now new_element */
        if(element->next == NULL)
            list->tail = new_element;
        /* Otherwise, need to update the prev pointer of the element now following new_element */
        else
            element->next->prev = new_element;

        /* Update the next pointer of the existing element */
        element->next = new_element;
    }

    /* Update the size of the list */
    list->size += 1;

    /* If we get here, we are successful so return 0 */
    return 0;
}


/* Insert an element just before an existing element */
int dlist_insert_prev(DList *list, DListElement *element, const void *data)
{
    /* If element is NULL and the list is not empty, return an error */
    if( (element == NULL) && (dlist_size(list) != 0) )
        return -1;

    /* The new element to be added */
    DListElement *new_element = malloc(sizeof(DListElement));
    if(new_element == NULL)
        return -1;

    /* Set data member to provided data */
    new_element->data = (void *)data;

    /* Handle insertion when list is empty */
    if(dlist_size(list) == 0)
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    /* Otherwise, handle insertion when list is nonempty */
    else
    {
        new_element->next = element;
        new_element->prev = element->prev;

        /* If element was the head, the new head is now new_element */
        if(element->prev == NULL)
            list->head = new_element;
        /* Otherwise, need to update the next pointer of the element now preceding new_element */
        else
            element->prev->next = new_element;

        /* Update the prev pointer of the existing element */
        element->prev = new_element;
    }

    /* Update the size of the list */
    list->size += 1;

    /* If we get here, we are successful so return 0 */
    return 0;
}


/* Remove an element from the list */
int dlist_remove(DList *list, DListElement *element, void **data)
{
    /* If supplied element is NULL or the list is empty, return an error */
    if( (element == NULL) || (dlist_size(list) == 0) )
        return -1;

    /* data now points to the data associated with the element to be removed */
    *data = element->data;

    /* Handle removal of element at head of list */
    if(element == list->head)
    {
        /* Update the head */
        list->head = element->next;

        /* If the list only had one element, update the tail to be NULL (i.e., make the list empty) */
        if(list->head == NULL)
            list->tail = NULL;
        /* Otherwise, make the prev pointer of the new head point to NULL */
        else
            element->next->prev = NULL;
    }
    /* Otherwise, handle removal of an element not at the head of the list */
    else
    {
        /* Update the next pointer of the element prior to the one being removed */
        element->prev->next = element->next;

        /* If the element we removed was the tail, update the tail of the list */
        if(element->next == NULL)
            list->tail = element->prev;
        /* Otherwise, update the prev pointer of the element after the one being removed */
        else
            element->next->prev = element->prev;
    }

    /* Free the storage allocated by the DListElement */
    free(element);

    /* Update the size of the list */
    list->size -= 1;

    /* If we get here, we are successful so return 0 */
    return 0;
}

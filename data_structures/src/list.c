/* Implementation of Linked List */
#include <stdlib.h>
#include <string.h>

#include "list.h"


/* Initialize a Linked List */
void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}


/* Destroy a Linked List */
void list_destroy(List *list)
{
    /* Will hold the data in each element */
    void *data;

    /* Remove each element in the list */
    while(list_size(list) > 0)
    {
        /* Continuously remove the head element.  If the user supplied a destroy function, apply it to the data */  
        if( (list_remove_next(list, NULL, (void **)&data) == 0) && (list->destroy != NULL) )
            list->destroy(data);
    }

    /* To be safe, clear the structure */
    memset(list, 0, sizeof(List));
    
}


/* Insert a new element into the list */
int list_insert_next(List *list, ListElement *element, const void *data)
{
    /* Allocate storage for new element */
    ListElement *new_element = malloc(sizeof(ListElement));
    if(new_element == NULL)
        return -1;

    /* Set data member to provided data */
    new_element->data = (void *)data;

    /* Handle insertion at head of the list */
    if(element == NULL)
    {
        if(list_size(list) == 0)
            list->tail = new_element;

        new_element->next = list->head;
        list->head = new_element;
    }
    /* Handle insertion elsewhere */
    else
    {
        if(element->next == NULL)
            list->tail = new_element;

        new_element->next = element->next;
        element->next = new_element;
    }

    /* Update the size of the list */
    list->size += 1;

    /* If we get here, we are successful so return 0 */
    return 0;
}


/* Remove an element from the list */
int list_remove_next(List *list, ListElement *element, void **data)
{
    /* If list is empty, cannot remove anything */
    if(list_size(list) == 0)
        return -1;

    /* Used to hold the element to be removed */
    ListElement *old_element;

    /* Handle removal from head */
    if(element == NULL)
    {
        /* data now points to the data stored in the head element */
        *data = list->head->data;

        old_element = list->head;
        list->head = list->head->next;

        /* If the size of the list was 1, we have now created a list of size 0 so point tail to NULL */
        if(list_size(list) == 1)
            list->tail = NULL;
    }
    /* Handle removal elsewhere */
    else
    {
        /* Cannot remove something after the tail! */
        if(element->next == NULL)
            return -1;

        /* data now points to data stored in element to be removed */
        *data = element->next->data;

        old_element = element->next;
        element->next = element->next->next;

        /* If we removed the tail, set the new tail */
        if(element->next == NULL)
            list->tail = element;
    }

    /* Free storage allocated by the List datatype */
    free(old_element);

    /* Update the size of the list */
    list->size -= 1;

    /* If we get here, we are successful */
    return 0;
}

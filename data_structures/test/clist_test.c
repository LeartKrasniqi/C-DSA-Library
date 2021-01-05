/* Testing Circular Linked List Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "clist.h"

void print_list(CList *list);

typedef struct Node_ {
    int id;
} Node;

/* Test the methods and macros of a clist
    Methods:
      - clist_init()
      - clist_destroy()
      - clist_insert_next()
      - clist_remove_next()
    Macros:
      - clist_size()
      - clist_head()
      - clist_data()
      - clist_next()
*/
int main()
{
    /* Allocate memory for the clist */
    CList *list = malloc(sizeof(*list));
    if(list == NULL)
        return -1;

    /* Initialize the clist */
    clist_init(list, free);

    /* Create some nodes and insert them */
    for(int i = 0; i < 5; i++)
    {
        Node *n = malloc(sizeof(*n));
        n->id = i;
        clist_insert_next(list, clist_head(list), n);
    }
    printf("--- Inserted nodes ---\n");
    print_list(list);
    printf("\n");

    /* Remove some elements */
    Node *data[2];
    clist_remove_next(list, clist_head(list), (void **)&data[0]);
    clist_remove_next(list, clist_next(clist_head(list)), (void **)&data[1]);
    printf("--- Removed nodes ---\n");
    printf("Removed ids: %d  %d\n", data[0]->id, data[1]->id);
    print_list(list);
    printf("\n");

    /* Test out whether list is circular */
    CListElement *e = clist_head(list);
    for(int i = 0; i < clist_size(list); i++)
        e = clist_next(e);
    printf("--- Testing other stuff ---\n");
    printf("circularity: %s\n", (e == clist_head(list)) ? "pass" : "fail");

    /* Destroy the clist */
    clist_destroy(list);
    return 0;
}

void print_list(CList *list)
{
    printf("Size: %d, Contents: ", clist_size(list));
    CListElement *e = clist_head(list);
    for(int i = 0; i < clist_size(list); i++)
    {
        Node *data = (Node *)clist_data(e);
        printf("%d  ", data->id);
        e = clist_next(e);
    }
    printf("\n");
}
        

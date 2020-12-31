/* Testing list implementation */
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void print_list(List *list);

typedef struct Node_ {
    char *name;
    int id;
} Node;

/* Test the various methods and macros for list
    methods:
      - list_init()
      - list_destroy()
      - list_insert_next()
      - list_remove_next()
    macros:
      - list_size()
      - list_head()
      - list_is_head()
      - list_tail()
      - list_is_tail()
      - list_data()
      - list_next()
*/
int main()
{
    /* Allocate memory for a list and initialize */
    List *list = malloc(sizeof(*list));
    if(list == NULL)
        return -1;
    list_init(list, NULL);

    /* Make some nodes and insert them into the list */
    Node n1 = {"foo", 1};
    Node n2 = {"bar", 12};
    Node n3 = {"blah", 55};
    Node n4 = {"yay", 0};
    list_insert_next(list, list_head(list), &n1);
    list_insert_next(list, list_tail(list), &n2);
    list_insert_next(list, list_tail(list), &n3);
    list_insert_next(list, list_tail(list), &n4);

    printf("---- Inserted nodes ----\n");
    print_list(list);
    printf("\n");

    /* Remove the third element */
    ListElement *e = list_next(list_head(list));
    Node *data;
    if(list_remove_next(list, e, (void **)&data) != 0)
        return -1;
    printf("--- Removed third node ---\n");
    printf("Third node: ('%s', %d)\n", data->name, data->id);
    print_list(list);
    printf("\n");

    /* Testing the remaining macros */
    printf("--- Checking remaining macros ---\n");
    printf("list_is_head: %s\n", (list_is_head(list, list_head(list)) ? "pass" : "fail"));
    printf("list_is_tail: %s\n", (list_is_tail(list_tail(list)) ? "pass" : "fail"));
    printf("\n");
    
    /* Destroy the list */
    list_destroy(list);

    return 0;
}

/* Print out list and test the list_size macro */
void print_list(List *list)
{
    printf("Size: %d, Contents: ", list_size(list));
    for(ListElement *e = list_head(list); e != NULL; e = list_next(e))
    {
        Node *data = (Node *)list_data(e);
        printf("('%s', %d)  ", data->name, data->id);
    }
    printf("\n");
}


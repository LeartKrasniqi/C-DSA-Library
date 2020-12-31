/* Testing Doubly Linked List Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

void print_list(DList *list);

typedef struct Component_ {
    char *ip_addr;
    char *name;
} Component;

/* Test the methods and macros of a dlist
    Methods:
      - dlist_init()
      - dlist_destroy()
      - dlist_insert_next()
      - dlist_insert_prev()
      - dlist_remove()
    Macros:
      - dlist_size()
      - dlist_head()
      - dlist_is_head()
      - dlist_tail()
      - dlist_is_tail()
      - dlist_data()
      - dlist_next()
      - dlist_prev()
*/
int main()
{
    /* Create dlist and initialize */
    DList *list = malloc(sizeof(*list));
    if(list == NULL)
        return -1;

    /* Since we use free as the destroy function, the data we insert should be dynamically allocated */
    dlist_init(list, free);

    /* Create some data */
    Component *c1 = malloc(sizeof(*c1));
    c1->ip_addr = "192.168.1.1";
    c1->name = "router";

    Component *c2 = malloc(sizeof(*c2));
    c2->ip_addr = "192.168.1.5";
    c2->name = "printer";

    /* Insert into dlist */
    dlist_insert_next(list, dlist_head(list), c1);
    dlist_insert_next(list, dlist_head(list), c2);
    printf("--- Initial insert ---\n");
    print_list(list);
    printf("\n");

    /* Insert new element at head */
    Component *c3 = malloc(sizeof(*c3));
    c3->ip_addr = "192.168.1.7";
    c3->name = "MacBook";
    dlist_insert_prev(list, dlist_head(list), c3);
    printf("--- Insert something prior to head ---\n");
    print_list(list);
    printf("\n");

    /* Remove the tail element */
    Component *data;
    dlist_remove(list, dlist_tail(list), (void **)&data);
    printf("--- Remove the tail element ---\n");
    printf("Removed element: ('%s', '%s')\n", data->ip_addr, data->name);
    print_list(list);

    /* Test other macros */
    printf("--- Testing other macros ---\n");
    printf("dlist_is_head: %s\n", (dlist_is_head(dlist_head(list)) ? "pass" : "fail" ));
    printf("dlist_is_tail: %s\n", (dlist_is_tail(dlist_tail(list)) ? "pass" : "fail" ));
    printf("dlist_next: %s\n", (dlist_is_tail(dlist_next(dlist_prev(dlist_tail(list)))) ? "pass" : "fail" ) );
    printf("dlist_prev: %s\n", (dlist_is_head(dlist_prev(dlist_next(dlist_head(list)))) ? "pass" : "fail" ) );
    
    /* Destroy the dlist */
    dlist_destroy(list);

    return 0;
}

/* Print the size of the list and its contents */
void print_list(DList *list)
{
    printf("Size: %d, Contents: ", dlist_size(list));
    for(DListElement *e = dlist_head(list); e != NULL; e = dlist_next(e))
    {
        Component *data = (Component *)dlist_data(e);
        printf("('%s', '%s')  ", data->ip_addr, data->name);
    }
    printf("\n");
}

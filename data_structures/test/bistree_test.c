/* Test of Binary Search Tree implementation */
#include <stdio.h>
#include <stdlib.h>

#include "bistree.h"

void print_tree(BisTree *tree);
void print_node(BiTreeNode *node, int level);
int compare(const void *key1, const void *key2);

typedef struct Employee_ {
    int id;
    char *name;
} Employee;

/* Testing the following methods and macros:
    Methods:
      - bistree_init()
      - bistree_destroy()
      - bistree_insert()
      - bistree_remove()
      - bistree_lookup()
    Macros:
      - bistree_size()
*/
int main()
{
    /* Allocate memory for the tree and initialize */
    BisTree *tree = malloc(sizeof(*tree));
    if(tree == NULL)
        return -1;
    bistree_init(tree, compare, NULL);

    /* Create some Employee names */
    char *names[4] = {"Jake", "Finn", "Ice King", "Gunter"};

    /* Insert Employees into tree */
    for(int i = 0; i < 4; i++)
    {
        Employee *e = malloc(sizeof(*e));
        e->id = i;
        e->name = names[i];
        bistree_insert(tree, (void *)e);
    }

    /* Print out the tree */
    printf("---- Inserted Employees ----\n");
    print_tree(tree);
    printf("\n");

    /* Remove an element */
    Employee *removed = malloc(sizeof(*removed));
    removed->id = 1;
    bistree_remove(tree, (void *)removed);
    printf("---- Removed Employee ----\n");
    printf("Lazily Removed Employee with id: %d\n", removed->id);
    print_tree(tree);
    printf("\n");

    /* Perform some lookups */ 
    printf("---- Lookups ----\n");
    Employee *lookups[5];
    for(int i = 0; i < 5; i++)
    {
        lookups[i] = malloc(sizeof(*lookups));
        lookups[i]->id = i;
        printf("Looking for Employee with id %d: ", i);
        if(bistree_lookup(tree, (void *)&lookups[i]) == 0)
            printf("(%d, %s)", lookups[i]->id, lookups[i]->name);
        else
            printf("Not found!");
        printf("\n");
    }

    /* Destroy the tree */
    bistree_destroy(tree); 

    return 0;
}

/* Print out the tree 
    Gets printed out like:

    ROOT
      LEFT
      RIGHT
*/
void print_tree(BisTree *tree)
{
    printf("Size: %d\n", bistree_size(tree)); 
    print_node(bitree_root(tree), 0);
}

/* Recursively print out each node */
void print_node(BiTreeNode *n, int level)
{
    /* Check if node is end of branch (i.e., NULL) or if it is hidden and do not print */
    if(bitree_is_eob(n))
        return;

    /* If node is hidden, move on to its children */
    if( ((AvlNode *)bitree_data(n))->hidden )
    {
        print_node(bitree_left(n), level + 1);
        print_node(bitree_right(n), level + 1);
        return;
    }

    /* Print spaces for pretty-print */
    for(int i = 0; i < level; i++)
        printf("  ");

    /* Print out the contents of the node */
    void *data = ((AvlNode *)bitree_data(n))->data;;
    Employee *e = (Employee *)data;
    printf("(%d, %s)\n", e->id, e->name);

    /* Print out the left and right children */
    print_node(bitree_left(n), level + 1);
    print_node(bitree_right(n), level + 1);
}

/* Compare employees based on their id */
int compare(const void *key1, const void *key2)
{
    int id1 = ((Employee *)key1)->id;
    int id2 = ((Employee *)key2)->id;

    if(id1 > id2)
        return 1;
    else if(id1 == id2)
        return 0;
    else
        return -1;
}

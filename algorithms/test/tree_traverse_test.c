/* Simple test for tree traversal implementations */
#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"
#include "tree_traverse.h"

void tree_helper(BiTree *tree, int *data);
void print_tree(BiTree *tree);
void print_node(BiTreeNode *n, int level);
void print_list(List *list, char *name);

/* Testing the following methods:
     - preorder()
     - inorder()
     - postorder()
*/
int main()
{
    /* Create a binary tree and insert some ints into it */
    BiTree *left = malloc(sizeof(*left));
    int data1[] = {2,4,5};
    tree_helper(left, data1);   
    BiTree *right = malloc(sizeof(*right));
    int data2[] = {3,6,7};
    tree_helper(right, data2);
    BiTree *tree = malloc(sizeof(*tree));
    int data0 = 0;
    bitree_merge(tree, left, right, (void *)&data0);

    /* Print the tree */
    print_tree(tree);

    /* Perform each of the traversals */
    List *preorder_list = malloc(sizeof(List)), 
         *inorder_list = malloc(sizeof(List)), 
         *postorder_list = malloc(sizeof(List));
    list_init(preorder_list, NULL);
    list_init(inorder_list, NULL);
    list_init(postorder_list, NULL);
    preorder(bitree_root(tree), preorder_list);
    inorder(bitree_root(tree), inorder_list);
    postorder(bitree_root(tree), postorder_list);

    /* Print out the lists */
    print_list(preorder_list, "Preorder");
    print_list(inorder_list, "Inorder");
    print_list(postorder_list, "Postorder");

    return 0;
}

void tree_helper(BiTree *tree, int *data)
{
    bitree_init(tree, NULL);
    bitree_insert_left(tree, NULL, (void *)&data[0]);
    bitree_insert_left(tree, bitree_root(tree), (void *)&data[1]);
    bitree_insert_right(tree, bitree_root(tree), (void *)&data[2]);
}

void print_tree(BiTree *tree)
{
    printf("Size: %d\n", bitree_size(tree));
    print_node(bitree_root(tree), 0);
}

void print_node(BiTreeNode *n, int level)
{
    if(bitree_is_eob(n))
        return;

    /* Pretty-print */
    for(int i = 0; i < level; i++)
        printf("  ");

    /* Print out contents of node */
    int data = *((int *)bitree_data(n));
    printf("%d\n", data);

    /* Print out left and right children */
    print_node(bitree_left(n), level + 1);
    print_node(bitree_right(n), level + 1);
}

void print_list(List *list, char *name)
{
    printf("List: %s, Size: %d, Contents: ", name, list_size(list));
    for(ListElement *e = list_head(list); e != NULL; e = list_next(e))
    {
        int data = *((int *)list_data(e));
        printf("%d  ", data);
    }
    printf("\n");
}



/* Header file for Binary Trees */
#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>


/* Structure definition for binary tree node */
typedef struct BiTreeNode_{
    void *data;                 /* Will hold the data associated with this node */
    struct BiTreeNode_ *left;   /* Left child */
    struct BiTreeNode_ *right;  /* Right child */
} BiTreeNode;

/* Structure definition for the binary tree itself */
typedef struct BiTree_ {
    int size;           /* Number of nodes in the tree */

    int (*compare)(const void *key1, const void *key2);     /* Comparison function (not used in BiTree, but used in derived structures) */ 
    void (*destroy)(void *data);                            /* Deallocation function (e.g., free()) */

    BiTreeNote *root;   /* The root (i.e., top node) of the tree */
} BiTree;




/*
*********************************
        Interface Methods
*********************************
*/

/* Initialize a binary tree
    @param tree     The allocated BiTree structure
    @param destroy  Pointet to function used for deallocation

    Notes:
      - Must be called before other binary tree operations can be used
      - If binary tree contains data that should not be freed, set destroy to NULL
      - Complexity: O(1)
*/
void bitree_init(BiTree *tree, void (*destroy)(void *data));


/* Destroy a binary tree
    @param tree  The allocated BiTree structure to be destroyed

    Notes:
      - Calls the function passed as destroy to bitree_init() once for each node 
      - Complexity: O(n), where n is the number of nodes
*/
void bitree_destroy(BiTree *tree);


/* Insert a node as a left child
    @param tree  The allocated tree structure
    @param node  The parent node
    @param data  The data associated with the node to be added

    @return 0 if insertion successful, -1 otherwise

    Notes:
      - node should not already have a left child
      - If node is NULL, the new node is inserted as the root node (tree must be empty)
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int bitree_insert_left(BiTree *tree, BiTreeNode *node, const void *data);


/* Insert a node as a right child
    @param tree  The allocated tree structure
    @param node  The parent node
    @param data  The data associated with the node to be added

    @return 0 if insertion successful, -1 otherwise

    Notes:
      - node should not already have a right child
      - If node is NULL, the new node is inserted as the root node (tree must be empty)
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(1)
*/
int bitree_insert_right(BiTree *tree, BiTreeNode *node, const void *data);


/* Remove the subtree rooted at left node
    @param tree  The allocated tree structure
    @param node  The root of the subtree to be removed

    Notes:
      - If node is NULL, all nodes in the tree are removed
      - Calls the function passed as destroy to bitree_init() once for each node
      - Complexity: O(n), where n is the number of nodes in the subtree
*/
void bitree_remove_left(BiTree *tree, BiTreeNode *node);


/* Remove the subtree rooted at right node
    @param tree  The allocated tree structure
    @param node  The root of the subtree to be removed

    Notes:
      - If node is NULL, all nodes in the tree are removed
      - Calls the function passed as destroy to bitree_init() once for each node
      - Complexity: O(n), where n is the number of nodes in the subtree
*/
void bitree_remove_right(BiTree *tree, BiTreeNode *node);


/* Merge two binary trees into one
    @param merge  The allocated tree structure which will hold the result of the merge
    @param left   The tree which will be merged as the left subtree
    @param right  The tree which will be merged as the right subtree
    @param data   The data associated with the root node of the merged tree

    @return 0 if merge is successful, -1 otherwise

    Notes:
      - bitree_init() is called for the binary tree merge, with destroy set to left->destroy
      - After merging is complete, left and right are as if bitree_destroy() had been called on them
      - Complexity: O(1)
*/
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);



/*
*****************************
        Useful Macros
*****************************
*/

/* Get the number of nodes in the tree */
#define bitree_size(tree) ((tree)->size)

/* Get the root node of the tree */
#define bitree_root(tree) ((tree)->root)

/* Check if node is end of branch */
#define bitree_is_eob(node) ((node) == NULL)

/* Check if node is leaf node */
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)

/* Get data associated with node */
#define bitree_data(node) ((node)->data)

/* Get left child of node */
#define bitree_left(node) ((node)->left)

/* Get right child of node */
#define bitree_right(node) ((node)->right)

#endif

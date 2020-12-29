/* Header for Binary Search Tree */
#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

/* Balance factors for AVL trees */
#define AVL_LEFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RIGHT_HEAVY -1

/* Implement binary seach tree as AVL tree */
typedef struct AvlNode_ {
    void *data;     /* Data associated with node */
    int hidden;     /* Used to mark node if data is deleted */
    int factor;     /* Balance factor */
} AvlNode;

/* Binary Search Tree is just a binary tree */
typedef BiTree BisTree;




/*
*********************************
        Interface Methods
*********************************
*/

/* Initialize a binary search tree
    @param tree     The allocated BisTree structure
    @param compare  Function used to compare elements
    @param destroy  Function used for deallocation

    Notes:
      - Must be called before other binary search tree operations can be used
      - compare should return 1 if key1>key2, 0 if key1=key2, and -1 if key1<key2
      - If binary search tree contains data that should not be freed, set destroy to NULL
      - Complexity: O(1)
*/
void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));


/* Destroy a binary search tree
    @param tree  The allocated BisTree structure to be destroyed

    Notes:
      - Calls the function passed as destroy to bistree_init() once for each node
      - Compelxity: O(n), where n is the number of nodes in the tree
*/
void bistree_destroy(BisTree *tree);


/* Insert a node into a binary search tree
    @param tree  The allocated tree structure
    @param data  The data associated with the node to be added

    @return 0 if insertion successful, 1 if node already exists in tree, -1 otherwise

    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(log n), where n is the number of nodes in the tree
*/
int bistree_insert(BisTree *tree, const void *data);


/* Remove a node from a binary search tree
    @param tree  The allocated tree structure
    @param data  The data associated with the node to be removed

    @return 0 if removal was successful, -1 otherwise
    
    Notes:
      - Performs lazy-removal, simply marking the node with matching data as hidden
      - Data in the tree must remain valid even after it has been removed
      - Size does not decrease after removal
      - Complexity: O(log n), where n is the number of nodes in the tree
*/
int bistree_remove(BisTree *tree, const void *data);


/* Find a node in a binary search tree
    @param tree  The allocated tree structure
    @param data  The data associated with the node trying to be found

    @return 0 if the data is found, -1 otherwise

    Notes:
      - If a node with matching data is found, data points to the data in the tree upon return
      - Complexity: O(log n), where n is the number of nodes in the tree
*/
int bistree_lookup(BisTree *tree, void **data);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get number of nodes in binary search tree */
#define bistree_size(tree) ((tree)->size)

#endif 

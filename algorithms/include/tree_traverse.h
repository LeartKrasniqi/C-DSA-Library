/* Interface for Tree Traversal Methods */
#ifndef _TREE_TRAVERSE_H
#define _TREE_TRAVERSE_H

#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "bitree.h"


/* Perform preorder, inorder, or postorder traversal
    @param node  The current node
    @param list  The list containing all of the found nodes

    @return 0 if successful, -1 otherwise

    Notes:
      - To begin traversal, set node to root node of tree
      - list should be initialized via list_init()
      - Nodes are placed into the list in the order they are encountered
*/
int preorder(const BiTreeNode *node, List *list);
int inorder(const BiTreeNode *node, List *list);
int postorder(const BiTreeNode *node, List *list);

#endif

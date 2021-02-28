/* Implementation of Tree Traversal Methods */
#include "tree_traverse.h"

/* Preorder Travsersal */
int preorder(const BiTreeNode *node, List *list)
{
    if(!bitree_is_eob(node))
    {
        /* Insert this node into the list */
        if(list_insert_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        /* Traverse left-child */
        if(!bitree_is_eob(bitree_left(node)))
            if(preorder(bitree_left(node), list) != 0)
                return -1;

        /* Traverse right-child */
        if(!bitree_is_eob(bitree_right(node)))
            if(preorder(bitree_right(node), list) != 0)
                return -1;
    }

    return 0;
}


/* Inorder Traversal */
int inorder(const BiTreeNode *node, List *list)
{
    if(!bitree_is_eob(node))
    {
        /* Traverse left-child */
        if(!bitree_is_eob(bitree_left(node)))
            if(inorder(bitree_left(node), list) != 0)
                return -1;

        /* Insert this node into the list */
        if(list_insert_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        /* Traverse right-child */
        if(!bitree_is_eob(bitree_right(node)))
            if(inorder(bitree_right(node), list) != 0)
                return -1;
    }

    return 0;
}


/* Postorder Traversal */
int postorder(const BiTreeNode *node, List *list)
{
    if(!bitree_is_eob(node))
    {
        /* Traverse left-child */
        if(!bitree_is_eob(bitree_left(node)))
            if(postorder(bitree_left(node), list) != 0)
                return -1;

        /* Traverse right-child */
        if(!bitree_is_eob(bitree_right(node)))
            if(postorder(bitree_right(node), list) != 0)
                return -1;

        /* Insert this node into the list */
        if(list_insert_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;
    }

    return 0;
}


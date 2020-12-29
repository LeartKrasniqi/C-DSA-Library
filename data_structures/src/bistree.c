/* Implementation of Binary Search Trees */
#include <stdlib.h>
#include <string.h>

#include "bistree.h"


/*
********************************************
        Helper Function Declarations
********************************************
*/

static void destroy_left(BisTree *tree, BiTreeNode *node);
static void destroy_right(BisTree *tree, BiTreeNode *node);
static void rotate_left(BiTreeNode **node);
static void rotate_right(BiTreeNode **node);
static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced);
static int hide(BisTree *tree, BiTreeNode *node, const void *data);
static int lookup(BisTree *tree, BiTreeNode *node, void **data);



/*
***********************************************
        Interface Method Implemenations
***********************************************
*/

/* Initialize a binary search tree */
void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    /* Initialize the tree as a binary tree */
    bitree_init(tree, destroy);
    tree->compare = compare;
}


/* Destroy a binary search tree */
void bistree_destroy(BisTree *tree)
{
    /* Use helper function to destroy all nodes in the tree */
    destroy_left(tree, NULL);

    /* To be safe, clear the structure */
    memset(tree, 0, sizeof(BisTree));
}


/* Insert a node into a binary search tree */
int bistree_insert(BisTree *tree, const void *data)
{
    /* Initialize a balance factor for the node */
    int balanced = 0;

    /* Use helper function to recursively insert the node starting at the root of the tree */
    return insert(tree, &bitree_root(tree), data, &balanced);
}


/* Remove a node from a binary search tree */
int bistree_remove(BisTree *tree, const void *data)
{
    /* Use helper function to lazily remove node containing specified data */
    return hide(tree, bitree_root(tree), data);
}


/* Find a node in a binary search tree */
int bistree_lookup(BisTree *tree, void **data)
{
    /* Use helper function to recursively look for node containing specified data starting at the root of the tree */
    return lookup(tree, bitree_root(tree), data);
}




/*
***********************************************
        Helper Function Implementations
***********************************************
*/

/* Destroy the left subtree rooted at node */
static void destroy_left(BisTree *tree, BiTreeNode *node)
{
    /* Cannot destroy an empty tree */
    if(bitree_size(tree) == 0)
        return;

    /* Determine where to destroy nodes */
    BiTreeNode **position;
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->left;

    /* Destroy the nodes */
    if(*position != NULL)
    {
        /* Recursively destroy the children */
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        /* If user-defined destroy function is not NULL, use it on each node */
        if(tree->destroy != NULL)
            tree->destroy( ((AvlNode *)(*position)->data)->data );

        /* Free the AVL data and then the node itself */
        free((*position)->data);
        free(*position);
        *position = NULL;

        /* Update the size of tree */
        tree->size -= 1;
    }
}


/* Destroy the right subtree rooted at node */
static void destroy_right(BisTree *tree, BiTreeNode *node)
{
    /* Cannot destroy an empty tree */
    if(bitree_sisze(tree) == 0)
        return;

    /* Determine where to destroy nodes */
    BiTreeNode **position;
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->right;

    /* Destroy the nodes */
    if(*position != NULL)
    {
        /* Recursively destroy the children */
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        /* If user-define destroy function is not NULL, apply it to each node */
        if(tree->destroy != NULL)
            tree->destroy( ((AvlNode *)(*position)->data)->data );

        /* Free the AVL data and then the node itself */
        free((*position)->data);
        free(*position);
        *position = NULL;

        /* Update the size of the tree */
        tree->size -= 1;
    }
}


/* Perform a LL or LR rotation in order to balance the AVL tree */
static void rotate_left(BiTreeNode **node)
{
    /* Used to keep track of the left-child of the node */
    BiTreeNode *left = bitree_left(*node);  
    
    /* If the node is left-heavy, perform a LL rotation */
    if( (AvlNode *)bitree_data(left)->factor == AVL_LEFT_HEAVY )
    {
        /* First, set the left-child of node to the right-child of left */
        bitree_left(*node) = bitree_right(left);

        /* Then, set the right-child of left to node */
        bitree_right(left) = *node;

        /* Now, each node is balanced, so reflect that in the factor member */
        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;

        /* Set the pointer referencing node to left now to complete the rotation */
        *node = left;
    }
    /* Otherwise, perform a LR rotation */
    else
    {
        /* When dealing with LR rotation, we need to look at the grandchild of node (i.e., right-child of left) */ 
        BiTreeNode *grandchild = bitree_right(left);

        /* First, set the right-child of left to the left-child of grandchild */
        bitree_right(left) = bitree_left(grandchild);

        /* Second, set the left-child of grandchild to left */
        bitree_left(grandchild) = left;

        /* Then, set left-child of node to the right-child of grandchild */
        bitree_left(*node) = bitree_right(grandchild);

        /* Next, set the right-child of grandchild to node */
        bitree_right(grandchild) = *node;
        
        /* Adjusting balance factors after LR rotation depends on original balance factor of grandchild */ 
        switch( ((AvlNode *)bitree_data(grandchild))->factor )
        {
            /* If grandchild was left-heavy, node becomes right-heavy and left becomes balanced */
            case AVL_LEFT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_RIGHT_HEAVY;
                ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
                break;

            /* If grandchild was right-heavy, node becomes balanded and left becomes left-heavy */
            case AVL_RIGHT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *)bitree_data(left))->factor = AVL_LEFT_HEAVY;
                break;

            /* If grandchild was balanced, both node and left become balanced */
            case AVL_BALANCED: 
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
                break;
        }

        /* Now, grandchild is balanced */
        ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;

        /* Lastly, set the pointer referencing node to grandchild to complete the rotation */
        *node = grandchild;
    }
}


/* Perform a RR or RL rotation in order to balance the AVL tree */
static void rotate_right(BiTreeNode **node)
{
    /* Used to keep track of the right-child of the node */
    BiTreeNode *right = bitree_right(*node);

    /* If the node is right-heavy, perform a RR rotation */
    if( ((AvlNode *)bitree_data(right))->factor == AVL_RIGHT_HEAVY )
    {
        /* First, set the right-child of node to the left-child of right */
        bitree_right(*node) = bitree_left(right);

        /* Next, set the left-child of right to node */
        bitree_left(right) = *node;

        /* Now, each node is balanced so reflect that in the balance factor */
        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;

        /* Lastly, set the pointer referencing node to right in order to complete the rotation */
        *node = right;
    }
    /* Otherwise, perform a RL rotation */
    else
    {
        /* When dealing with a RL rotation, we need to look at the grandchild of node (i.e., left-child of right) */
        BiTreeNode *grandchild = bitree_left(right);

        /* First, set the left-child of right to the right-child of granchild */
        bitree_left(right) = bitree_right(grandchild);

        /* Second, set the right-child of grandchild to right */
        bitree_right(grandchild) = right;

        /* Then, set right-child of node to the left-child of grandchild */
        bitree_right(*node) = bitree_left(grandchild);

        /* Next, set the left-child of grandchild to node */
        bitree_left(grandchild) = *node;

        /* Adjusting balance factors after a RL rotation depends on original balance factor of grandchild */
        switch( ((AvlNode *)bitree_data(grandchild))->factor )
        {
            /* If grandchild was left-heavy, node becomes balanced and right becomes right-heavy */
            case AVL_LEFT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *)bitree_data(right))->factor = AVL_RIGHT_HEAVY;
                break;

            /* If grandchild was right-heavy, node becomes left-heavy and right becomes balanced */
            case AVL_RIGHT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_LEFT_HEAVY;
                ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
                break;

            /* If grandchild was balanced, both node and right become balanced */
            case AVL_BALANCED:
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
                break;
        }

        /* Now, grandchild is balanced */
        ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;

        /* Lastly, set the pointer referencing node to grandchild to complete the rotation */
        *node = grandchild;
    }
}


/* Insert a node into a tree */
static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced)
{
    AvlNode *avl_data;  /* Will be used as the data to be inserted in the tree (the actual data will be a member of this node) */
    int cmpval,         /* Will be used for comparison results */
        retval;         /* Will be used for recursive insertion results */


    /* Handle insertion into an empty tree */
    if(bitree_is_eob(*node))
    {
        /* Allocate memory for AvlNode */
        if((avl_data = malloc(sizeof(AvlNode))) == NULL)
            return -1;

        /* Initialize the AVL node as balanced, non-hidden, and containing the supplied data */
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;

        /* Use binary tree left-insertion to insert the AvlNode */
        return bitree_insert_left(tree, *node, avl_data);
    }
    /* Otherwise, handle insertion into a non-empty tree */
    else
    {
        /* Compare the data to be entered with the data in node (to see if we enter to the left or to the right) */
        cmpval = tree->compare(data, ((AvlNode *)bitree_data(*node))->data);
    
        /* Insert to the left */
        if(cmpval < 0)
        {
            /* Handle insertion if left-subtree is empty */
            if(bitree_is_eob(bitree_left(*node)))
            {
                /* Allocate memory for AvlNode */
                if((avl_data = malloc(sizeof(AvlNode))) == NULL)
                    return -1;

                /* Initialize AVL node */
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;

                /* Try to insert via binary tree left-insertion */
                if(bitree_insert_left(tree, *node, avl_data) != 0)
                    return -1;

                /* If left-insertion was successful, mark tree as imbalanced */
                *balanced = 0;
            }
            /* Otherwise, handle insertion if left-subtree is non-empty */
            else
            {
                /* Recursively call insert on the left-subtree */
                retval = insert(tree, &bitree_left(*node), data, balanced);

                /* If insertion failed, return the proper error */
                if(retval != 0)
                    return retval;
            }

            /* Ensure that the tree remains balanced */
            if(!(*balanced))
            {
                switch( ((AvlNode *)bitree_data(*node))->factor )
                {
                    /* If node was left-heavy, perform left-rotation which results in a balanced tree */
                    case AVL_LEFT_HEAVY:
                        rotate_left(node);
                        *balanced = 1;
                        break;

                    /* If node was right-heavy, we just added something to the left so it is now balanced (and so is the tree) */
                    case AVL_RIGHT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;

                    /* If node was balanced, we just added something to the left so it is now left-heavy and the tree is not balanced */
                    case AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_LEFT_HEAVY;
                        break;
                }
            }
        }
        /* Insert to the right */
        else if(cmpval > 0)
        {
            /* Handle insertion if right-subtree is empty */
            if(bitree_is_eob(bitree_right(*node)))
            {
                /* Allocate memory for AvlNode */
                if((avl_data = malloc(sizeof(AvlNode))) == NULL)
                    return -1;

                /* Initialize AVL Node */
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;

                /* Try to insert via binary tree right-insertion */
                if(bitree_insert_right(tree, *node, avl_data) != 0)
                    return -1;

                /* If right-insertion was successful, mark tree as imbalanced */
                *balanced = 0;
            }
            /* Otherwise, handle insertion if right-subtree is non-empty */
            else
            {
                /* Recursively call insert on the right-subtree */
                retval = insert(tree, &bitree_right(*node), data, balanced);
                
                /* If insertion failed, return the proper error */
                if(retval != 0)
                    return retval;
            }

            /* Ensure that the tree remains balanced */
            if(!(*balanced))
            {
                switch( ((AvlNode *)bitree_data(*node))->factor )
                {
                    /* If the node was left-heavy, we just added something to the right so it is now balanced (and so is the tree) */
                    case AVL_LEFT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;

                    /* If the node was right-heavy, perform right-rotation which results in a balanced tree */
                    case AVL_RIGHT_HEAVY:
                        rotate_right(node);
                        *balanced = 1;
                        break;

                    /* If the node was balanded, we just added something to the right so it is now right-heavy and the tree is not balanced */
                    case AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_RIGHT_HEAVY;
                        break;
                }
            }
        }
        /* Otherwise, the data matches an existing node */
        else
        {
            /* If the data is in the tree and not hidden, do nothing */
            if( !((AvlNode *)bitree_data(*node))->hidden )
                return 1;

            /* Otherwise, destroy the hidden data since it is being replaced */
            if(tree->destroy != NULL)
                tree->destroy(((AvlNode *)bitree_data(*node))->data);
            
            /* Insert the new data and mark it as not hidden */
            ((AvlNode *)bitree_data(*node))->data = (void *)data;
            ((AvlNode *)bitree_data(*node))->hidden = 0;

            /* No need to rebalance since the tree structure has remained the same */
            *balanced = 1;
        }
    }
    
    /* If we get here, then insertion was successful so return 0 */
    return 0;
}    


/* Mark a node as hidden */
static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{ 
    int cmpval,         /* Will be used for comparison results */
        retval;         /* Will be used for recursive insertion results */

    /* If node is end-of-branch, return that data was not found */
    if(bitree_is_eob(node))
        return -1;

    /* Compare the data desired to be hidden with the data associated with node */
    cmpval = tree->compare(data, ((AvlNode *)bitree_data(node))->data);

    /* Recursively move to the left */
    if(cmpval < 0)
        retval = hide(tree, bitree_left(node), data);
    /* Recursively move to the right */
    else if(cmpval > 0)
        retval = hide(tree, bitree_right(node), data);
    /* Otherwise, mark the node as hidden */
    else
    {
        ((AvlNode *)bitree_data(node))->hidden = 1;
        retval = 0;
    }

    return retval;
}


/* Find node with specific data */
static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
    int cmpval,         /* Will be used for comparison results */
        retval;         /* Will be used for recursive insertion results */

    /* If node is end-of-branch, return that data was not found */
    if(bitree_is_eob(node))
        return -1;

    /* Compare the data desired to be found with the data associated with node */
    cmpval = tree->compare(*data, ((AvlNode *)bitree_data(node))->data);

    /* Recursively move to the left */
    if(cmpval < 0)
        retval = lookup(tree, bitree_left(node), data);
    /* Recursively move to the right */
    else if(cmpval > 0)
        retval = lookup(tree, bitree_right(node), data);
    /* Otherwise, analyze this node */
    else
    {
        /* If this node is not hidden, pass back the data from the tree */
        if( !((AvlNode *)bitree_data(node))->hidden )
        {
            *data = ((AvlNode *)bitree_data(node))->data;
            retval = 0;
        }
        /* Otherwise, return that the data was not found */
        else
            return -1;
    }

    return retval;
}


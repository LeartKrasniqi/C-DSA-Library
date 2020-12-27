/* Implementation of Binary Trees */
#include <stdlib.h>
#include <string.h>

#include "bitree.h"


/* Initialize a binary tree */
void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}


/* Destroy a binary tree */
void bitree_destroy(BiTree *tree)
{
    /* Remove all nodes from the tree */
    bitree_remove_left(tree, NULL);

    /* To be safe, clear the structure */
    memset(tree, 0, sizeof(BiTree));
}


/* Insert a node as a left child */
int bittree_insert_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    /* Will point to the position where the node will be inserted */
    BiTreeNode **position;

    /* Try to insert at the root of the tree */
    if(node == NULL)
    {
        /* Only allow insertions at root if the tree is empty */
        if(bitree_size(tree) > 0)
            return -1;
        
        /* Mark the root as the position for the new node */
        position = &tree->root;
    }
    /* Otherwise, try to insert elsewhere in the tree */
    else
    {
        /* Only allow insertions at the end of a branch */
        if(bitree_left(node) != NULL)
            return -1;

        /* Mark the left child as the position for the new node */ 
        position = &node->left;
    }

    /* Allocate memory for the new node */
    BiTreeNode *new_node = malloc(sizeof(BiTreeNode));
    if(new_node == NULL)
        return -1;

    /* Insert the new_node into the tree */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    /* Update the size of the tree */
    tree->size += 1;

    /* If we get here, insertion was successful */
    return 0;
}


/* Insert node as a right child */
int bittree_insert_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    /* Will point to the position where the node will be inserted */
    BiTreeNode **position;

    /* Try to insert at the root of the tree */
    if(node == NULL)
    {
        /* Only allow insertions at root if the tree is empty */
        if(bitree_size(tree) > 0)
            return -1;
        
        /* Mark the root as the position for the new node */
        position = &tree->root;
    }
    /* Otherwise, try to insert elsewhere in the tree */
    else
    {
        /* Only allow insertions at the end of a branch */
        if(bitree_right(node) != NULL)
            return -1;

        /* Mark the right child as the position for the new node */ 
        position = &node->right;
    }

    /* Allocate memory for the new node */
    BiTreeNode *new_node = malloc(sizeof(BiTreeNode));
    if(new_node == NULL)
        return -1;

    /* Insert the new_node into the tree */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    /* Update the size of the tree */
    tree->size += 1;

    /* If we get here, insertion was successful */
    return 0;
}


/* Remove the subtree rooted at a left node */
void bitree_remove_left(BiTree *tree, BiTreeNode *node)
{
    /* If the tree is empty, just return */
    if(bitree_size(tree) == 0)
        return;

    /* Find the position where to remove the nodes -- Either the root of the tree or left child of node */
    BiTreeNode **position;
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->left;

    /* Remove the nodes from that position */
    if(*position != NULL)
    {
        /* Recursively remove the left and right subtrees rooted at the position */
        bitree_remove_left(tree, *position);
        bitree_remove_right(tree, *position);

        /* Call a user-defined function to free the data */
        if(tree->destroy != NULL)
            tree->destroy((*position)->data);

        /* Free the root position node itself */ 
        free(*position);
        *position = NULL;

        /* Update the size of the tree */
        tree->size -= 1;
    }
}


/* Remove the subtree rooted at a right node */
void bitree_remove_right(BiTree *tree, BiTreeNode *node)
{
    /* If the tree is empty, just return */
    if(bitree_size(tree) == 0)
        return;

    /* Find the position where to remove the nodes -- Either the root of the tree or left child of node */
    BiTreeNode **position;
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->right;

    /* Remove the nodes from that position */
    if(*position != NULL)
    {
        /* Recursively remove the left and right subtrees rooted at the position */
        bitree_remove_left(tree, *position);
        bitree_remove_right(tree, *position);

        /* Call a user-defined function to free the data */
        if(tree->destroy != NULL)
            tree->destroy((*position)->data);

        /* Free the root position node itself */ 
        free(*position);
        *position = NULL;

        /* Update the size of the tree */
        tree->size -= 1;
    }
}


/* Merge two binary trees into one */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    /* Initialize the merged tree */
    bitree_init(merge, left->destroy);

    /* Try to insert the data for the root node of the merged tree -- Destroy merge and return error if this fails */
    if(bitree_insert_left(merge, NULL, data) != 0)
    {
        bitree_destroy(merge);
        return -1;
    }

    /* Merge the two trees into one */
    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bittree_root(right);

    /* Update the size of the tree */
    merge->size += bitree_size(left) + bitree_size(right);

    /* Do not let the original trees access the merged nodes */
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}


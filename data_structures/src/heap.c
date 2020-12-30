/* Implementation of Heaps */
#include <stdlib.h>
#include <string.h>

#include "heap.h"

/*
*************************************
        Private Useful Macros
*************************************
*/

/* Get array index of parent of node at index npos */
#define heap_parent(npos) ((int)((npos) - 1) / 2)

/* Get array index of left-child of node at index npos */ 
#define heap_left(npos) (((npos) * 2) + 1)

/* Get array index of right-child of node at index npos */
#define heap_right(npos) (((npos) * 2) + 2)




/*
************************************************
        Interface Method Implementations
************************************************
*/

/* Initialize a heap */
void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;
}


/* Destroy a heap */
void heap_destroy(Heap *heap)
{
    /* If user supplied a destroy function, apply it to each node in the heap */
    if(heap->destroy != NULL)
        for(int i = 0; i < heap_size(heap); i++)
            heap->destroy(heap->tree[i]);

    /* Free the storage allocated for the heap and clear the structure to be safe */
    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
}


/* Insert a node into a heap */
int heap_insert(Heap *heap, const void *data)
{
    /* Used as a temp pointer for allocation and swapping */
    void *temp;
    
    /* Allocate storage for the new node and properly set the tree-array in heap */
    temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *));
    if(temp == NULL)
        return -1;
    else
        heap->tree = temp;

    /* Insert the new node after the last node in the heap */
    heap->tree[heap_size(heap)] = (void *)data;

    /* Obtain indices of current node and its parent to begin heapifying */
    int cur_pos = heap_size(heap);
    int par_pos = heap_parent(cur_pos);

    /* Heapify the tree by pushing the contents of the new node upward */
    while( (cur_pos > 0) && (heap->compare(heap->tree[par_pos], heap->tree[cur_pos]) < 0) )
    {
        /* Swap the contents of the current node and its parent */
        temp = heap->tree[par_pos];
        heap->tree[par_pos] = heap->tree[cur_pos];
        heap->tree[cur_pos] = temp;

        /* Move up a level to continue heapifying */
        cur_pos = par_pos;
        par_pos = heap_parent(cur_pos);
    }

    /* Update the size of the heap */
    heap->size += 1;

    /* If we get here, insertion was successful */
    return 0;
}


/* Extract the top node from a heap */
int heap_extract(Heap *heap, void **data)
{
    /* Cannot extract from an empty heap */
    if(heap_size(heap) == 0)
        return -1;

    /* Used as a temp pointer for allocation and swapping */
    void *temp;

    /* Extract the node at the top of the heap (i.e., first element in tree-array) */
    *data = heap->tree[0];

    /* Save the contents of the last node in the heap */
    void *save = heap->tree[heap_size(heap) - 1];

    /* Adjust the storage used by the heap */
    if(heap_size(heap) - 1 > 0)
    {
        /* Reallocate the tree-array */
        temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *));
        if(temp == NULL)
            return -1;
        else
            heap->tree = temp;

        /* Update the size */
        heap->size -= 1;
    }
    /* Handle the case when extracting the last (and only) node */
    else
    {
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    /* Copy the saved node to the top of the heap */
    heap->tree[0] = save;

    /* Obtain positions of current node, left-child, and right-child to begin heapifying */
    int cur_pos = 0,
        lft_pos = heap_left(cur_pos),
        rgt_pos = heap_right(cur_pos),
        swp_pos;    /* Used to keep track of the swapping position */
    
    /* Heapify the tree by pushing the contents of the new top downward */
    while(1)
    {
        /* Update the left and right child indices in each iteration of the loop */
        lft_pos = heap_left(cur_pos);
        rgt_pos = heap_right(cur_pos);
    
        /* Check to see if we should swap with the left child */
        if( (lft_pos < heap_size(heap)) && (heap->compare(heap->tree[lft_pos], heap->tree[cur_pos]) > 0) )
            swp_pos = lft_pos;
        else
            swp_pos = cur_pos;
        
        /* Now check to see if we should swap with the right child */
        if( (rgt_pos < heap_size(heap)) && (heap->compare(heap->tree[rgt_pos], heap->tree[swp_pos]) > 0) )
            swp_pos = rgt_pos;

        /* If swp_pos is cur_pos (i.e., no swap required), we good */
        if(swp_pos == cur_pos)
            break;
        
        /* Otherwise, we swap the contents of the current node and the selected child */
        temp = heap->tree[swp_pos];
        heap->tree[swp_pos] = heap->tree[cur_pos];
        heap->tree[cur_pos] = temp;

        /* Move down one level in the tree to continue heapifying */
        cur_pos = swp_pos;
    }

    /* If we get here, extraction was successful */
    return 0;
}


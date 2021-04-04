/* Header for Various Searching/Traversing Methods */
#ifndef _SEARCH_H
#define _SEARCH_H

#include <stdlib.h>
#include <string.h>

#include "bitree.h"
#include "graph.h"
#include "list.h"
#include "queue.h"



/*
***************************************
        Graph Search Structures
***************************************
*/

/* Vertex for Breadth-First Search */
typedef struct BfsVertex_ {
    void *data;         /* Data associated with vertex */
    VertexColor color;  /* Used to keep track of visited (and completed) vertices */
    int hops;           /* Number of traversals */
} BfsVertex;


/* Vertex for Depth-First Search */
typedef struct DfsVertex_ {
    void *data;         /* Data associated with vertex */
    VertexColor color;  /* Used to keep track of visited (and completed) vertices */
} DfsVertex;




/*
*********************************
        Interface Methods
*********************************
*/

/* Perform preorder, inorder, or postorder traversal of a BiTree
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


/* Perform Breadth-First Search on a Graph
    @param graph  The initialized Graph structure
    @param start  The starting (i.e., first) vertex
    @param hops   Allocated List which will contain vertices

    @return 0 if successful, -1 otherwise

    Notes:
      - hops should be allocated as a List, but does not need to be initialized
      - hops will contain list of vertices reachable from start
      - Complexity: O(V + E), where V is the number of vertices and E is the number of edges
*/
int bfs(Graph *graph, BfsVertex *start, List *hops);


/* Perform Depth-First Search on a Graph
    @param graph    The intitialized Graph structure
    @param start    The starting (i.e., first) vertex
    @param ordered  Initialized List which will contain vertices

    @return 0 if successful, -1 otherwise

    Notes:
      - When adding DfsVertex's to graph, make sure to set their color to 'white'
      - ordered should be initialized as a List
      - ordered will contain list of topologically-sorted vertices
      - Complexity: O(V + E), where V is the number of vertices and E is the number of edges
*/
int dfs(Graph *graph, DfsVertex *start, List *ordered);


/* Perform Binary Search on a Sorted Array
    @param sorted     Sorted array of elements
    @param target     Element to be found
    @param num_elem   Number of elements in sorted
    @param elem_size  Size of each element (in bytes)
    @param compare    Function used to compare elements

    @return index of target in sorted if found, -1 otherwise

    Notes:
      - If elements in sorted ascend, compare should return 1 if key1>key2, 0 if key1=key2, and -1 if key1<key2
      - If elements in sorted descend, reverse the above cases returing 1 and -1
      - Complexity: O(log(n)) where n is the number of elements to be searched
*/
int binary_search(void *sorted, void *target, int num_elem, int elem_size, int (*compare)(const void *key1, const void *key2));

#endif

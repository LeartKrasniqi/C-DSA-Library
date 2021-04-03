/* Header for Graph Searching Methods */
#ifndef _GRAPH_SEARCH_H
#define _GRAPH_SEARCH_H

#include "graph.h"
#include "list.h"
#include "queue.h"


/* Colors for graph vertices */
typedef enum VertexColor_ {white, gray, black} VertexColor;


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

/* Perform Breadth-First Search
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


/* Perform Depth-First Search
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

#endif

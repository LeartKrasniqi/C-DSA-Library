/* Header for Graphs */
#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>

#include "list.h"
#include "set.h"

/* Define a struct for adjacency lists */
typedef struct AdjList_ {
    void *vertex;   /* The vertex (i.e., node) with data */
    Set adjacent;   /* The actual list of adjacent vertices */
} AdjList;

/* Define a struct for graphs */
typedef struct Graph_ {
    int vcount;     /* Number of vertices */
    int ecount;     /* Number of edges */

    int (*match)(const void *key1, const void *key2);   /* Function to determine if two vertices match */
    void (*destroy)(void *data);                        /* Function used for deallocation */

    List adjlists;  /* The adjacency lists that make up the graph */
} Graph;

/* Define colors for vertices in graph */
typedef enum VertexColor_ {white, gray, black} VertexColor;


/*
*********************************
        Interface Methods
*********************************
*/

/* Initialize a graph
    @param graph    The allocated Graph structure
    @param match    Function used to match vertices
    @param destroy  Function used for deallocation

    Notes:
      - Must be called before other graph operations can be used
      - match should return 1 if key1=key2 and 0 otherwise
      - If graph contains data that should not be free, set destroy to NULL
      - Complexity: O(1)
*/
void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));


/* Destroy a graph
    @param graph  The graph structure to be destroyed

    Notes:
      - Calls the function passed as destroy to graph_init() once for each vertex
      - Complexity: O(V + E), where V is the number of vertices and E is the number of edges
*/
void graph_destroy(Graph *graph);


/* Insert a vertex into a graph
    @param graph  The initialized graph structure
    @param data   The data associated with the vertex to be inserted

    @return 0 if insertion was successful, 1 if the vertex already exists, and -1 otherwise
    
    Notes:
      - It is the responsibility of the caller to manage the storage associated with data
      - Complexity: O(V), where V is the number of vertices
*/
int graph_insert_vertex(Graph *graph, const void *data);


/* Insert an edge into a graph
    @param graph  The initialized graph structure
    @param data1  The source vertex
    @param data2  The sink vertex

    @return 0 if insertion was successful, 1 if the edge already exists, and -1 otherwise

    Notes:
      - Inserts an edges from vertex data1 to vertex data2
      - It is the responsibility of the caller to manage the storage associated with data2
      - To insert an edge (u,v) into an undirected graph, call this function twice: insert from u to v and then from v to u
      - Complexity: O(V), where V is the number of vertices
*/
int graph_insert_edge(Graph *graph, const void *data1, const void *data2);


/* Remove a vertex from a graph
    @param graph  The initialized graph structure
    @param data   The data associated with the vertex to be removed

    @return 0 if removing the vertex was successful, -1 otherwise

    Notes:
      - All edges to and from the vertex to be removed must have been removed previously (via graph_remove_edge())
      - Upon return, data will point to the data in the removed vertex
      - It is the responsibility of the caller to manage the storage associated with the removed data 
      - Complexity: O(V + E), where V is the number of vertices and E is the number of edges
*/ 
int graph_remove_vertex(Graph *graph, void **data);


/* Remove an edge from a graph
    @param graph  The initialized graph structure
    @param data1  The source vertex
    @param data2  The sink vertex

    @return 0 if removing the edge was successful, -1 otherwise

    Notes:
      - Removes the edge from data1 to data2
      - Upon return, data2 points to the data stored in the adjlist of the vertex specified by data1
      - It is the responsibility of the caller to manage the storage associated with the data
      - Complexity: O(V), where V is the number of vertices
*/
int graph_remove_edge(Graph *graph, void *data1, void **data2);

/* Retrieve adjacency list of specific vertex
    @param graph    The initialized graph structure
    @param data     The data associated with the vertex
    @param adjlist  The list of adjacent vertices

    @return 0 if retrieving the adjacency list is successful, -1 otherwise

    Notes:
      - A pointer to the actual adjacency list in the graph is returned, so it must not be manipulated by the caller
      - Complexity: O(V), where V is the number of vertices 
*/
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);


/* Check if vertex is adjacent to another 
    @param graph  The initialized graph structure
    @param data1  The data associated with the first vertex
    @param data2  The data associated with the second vertex

    @return 1 if the second vertex is adjacent to the first, 0 otherwise

    Notes:
      - Determines whether vertex specified by data2 is adjacent to vertex associated with data1
      - Complexity: O(V), where V is the number of vertices
*/
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);




/*
*****************************
        Useful Macros
*****************************
*/

/* Get the adjacency lists of the graph */
#define graph_adjlists(graph) ((graph)->adjlists)

/* Get the number of vertices in the graph */
#define graph_vcount(graph) ((graph)->vcount)

/* Get the number of edges in the graph */
#define graph_ecount(graph) ((graph)->ecount)

#endif

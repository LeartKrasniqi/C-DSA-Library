/* Testing Graph Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int match(const void *key1, const void *key2);
void print_graph(Graph *graph);
void print_adjlist(AdjList *adjlist);

/* Testing the following methods and macros
    Methods:
      - graph_init()
      - graph_destroy()
      - graph_insert_vertex()
      - graph_insert_edge()
      - graph_remove_vertex()
      - graph_remove_edge()
      - graph_adjlist()
      - graph_is_adjacent()
    Macros:
      - graph_adjlists()
      - graph_vcount()
      - graph_ecount()
*/
int main()
{
    /* Allocate memory for a directed graph */
    Graph *graph = malloc(sizeof(*graph));
    if(graph == NULL)
        return -1;

    /* Initialize */
    graph_init(graph, match, NULL);

    /* Insert vertices */
    int data[5] = {0,1,2,3,4};
    for(int i = 0; i < 5; i++)
        graph_insert_vertex(graph, (void *)&data[i]);

    /* Create edges */
    graph_insert_edge(graph, (void *)&data[0], (void *)&data[1]);
    graph_insert_edge(graph, (void *)&data[0], (void *)&data[3]);
    graph_insert_edge(graph, (void *)&data[1], (void *)&data[1]);
    graph_insert_edge(graph, (void *)&data[2], (void *)&data[4]);
    graph_insert_edge(graph, (void *)&data[4], (void *)&data[2]);
    graph_insert_edge(graph, (void *)&data[1], (void *)&data[2]);

    /* Print graph */
    printf("---- Created graph ----\n");
    print_graph(graph);
    printf("\n");

    /* Get adjacency list for some vertex */
    AdjList *v0_adj;
    graph_adjlist(graph, (void *)&data[0], &v0_adj);
    printf("---- Adjacency List ----\n");
    print_adjlist(v0_adj);
    printf("\n");

    /* Remove edges and a vertex */
    int *temp = malloc(sizeof(*temp));
    *temp = data[4];
    graph_remove_edge(graph, (void *)&data[2], (void **)&temp);
    temp = malloc(sizeof(*temp));
    *temp = data[2];
    graph_remove_edge(graph, (void *)&data[4], (void **)&temp);
    temp = malloc(sizeof(*temp));
    *temp = data[4];
    graph_remove_vertex(graph, (void **)&temp);
    printf("---- Removed vertex ----\n");
    print_graph(graph);
    printf("\n");

    /* Check for adjacency */
    printf("---- Checking adjacency ----\n");
    printf("Vertex %d is adjacent to Vertex %d: %s\n", data[1], data[0], graph_is_adjacent(graph, (void *)&data[0], (void *)&data[1]) ? "TRUE" : "FALSE");
    printf("Vertex %d is adjacent to Vertex %d: %s\n", data[0], data[1], graph_is_adjacent(graph, (void *)&data[1], (void *)&data[0]) ? "TRUE" : "FALSE");
    printf("Vertex %d is adjacent to Vertex %d: %s\n", data[1], data[1], graph_is_adjacent(graph, (void *)&data[1], (void *)&data[1]) ? "TRUE" : "FALSE");
    printf("Vertex %d is adjacent to Vertex %d: %s\n", data[3], data[2], graph_is_adjacent(graph, (void *)&data[2], (void *)&data[3]) ? "TRUE" : "FALSE");
    printf("Vertex %d is adjacent to Vertex %d: %s\n", data[2], data[2], graph_is_adjacent(graph, (void *)&data[2], (void *)&data[2]) ? "TRUE" : "FALSE");

    /* Destroy the graph */
    graph_destroy(graph);

    return 0;
}

int match(const void *key1, const void *key2)
{
    int val1 = *((int *)key1);
    int val2 = *((int *)key2);
    
    if(val1 == val2)
        return 1;
    else
        return 0; 
}

void print_graph(Graph *graph)
{
    printf("vcount = %d    ecount = %d\n", graph_vcount(graph), graph_ecount(graph));
    for(ListElement *v = list_head(&graph_adjlists(graph)); v != NULL; v = list_next(v))
    {
        AdjList *adjlist = (AdjList *)list_data(v);
        print_adjlist(adjlist);
    }
    printf("\n");
}

void print_adjlist(AdjList *adjlist)
{
    int *vertex = (int *)(adjlist->vertex);
    Set adj = (Set)(adjlist->adjacent);
    printf("Vertex %d:   ", *vertex);
    for(ListElement *s = list_head(&adj); s != NULL; s = list_next(s))
    {
        int *adj_vertex = (int *)list_data(s);
        printf("%d  ", *adj_vertex);
    }
    printf("\n");
}


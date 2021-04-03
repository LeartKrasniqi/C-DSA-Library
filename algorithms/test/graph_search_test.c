/* Testing Graph Searching Methods */
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "list.h"
#include "graph_search.h"


int match(const void *key1, const void *key2);
int bfs_match(const void *key1, const void *key2);
int dfs_match(const void *key1, const void *key2);

int main()
{
    /*
    ********************
            Data
    ********************
    */
    int data[6] = {0,1,2,3,4,5};
    BfsVertex *bfs_data = malloc(6 * sizeof(*bfs_data));
    DfsVertex *dfs_data = malloc(6 * sizeof(*dfs_data));

    /*
    *************************
            BFS Graph
    *************************
    */
    
    /* Create graph */
    Graph *bfs_graph = malloc(sizeof(*bfs_graph)); 
    if(bfs_graph == NULL)
        return -1;
    graph_init(bfs_graph, bfs_match, NULL);

    /* Insert vertices and edges */
    for(int i = 0; i < 6; i++)
    {
        bfs_data[i].data = &data[i];
        graph_insert_vertex(bfs_graph, (void *)&bfs_data[i]);
    }
    graph_insert_edge(bfs_graph, (void *)&bfs_data[0], (void *)&bfs_data[1]);
    graph_insert_edge(bfs_graph, (void *)&bfs_data[0], (void *)&bfs_data[3]);
    graph_insert_edge(bfs_graph, (void *)&bfs_data[1], (void *)&bfs_data[1]);
    graph_insert_edge(bfs_graph, (void *)&bfs_data[2], (void *)&bfs_data[4]);
    graph_insert_edge(bfs_graph, (void *)&bfs_data[4], (void *)&bfs_data[2]);
    graph_insert_edge(bfs_graph, (void *)&bfs_data[1], (void *)&bfs_data[2]);

    /* Select a start vertex */
    AdjList *bfs_adj;
    graph_adjlist(bfs_graph, (void *)&bfs_data[0], &bfs_adj);
    BfsVertex *bfs_start = bfs_adj->vertex;

    /* Create list to hold output vertices (and their hops) */
    List *bfs_vertices = malloc(sizeof(*bfs_vertices));
    
    /* Print graph */
    printf("---- BFS Graph ----\n");
    printf("vcount = %d    ecount = %d\n", graph_vcount(bfs_graph), graph_ecount(bfs_graph));
    for(ListElement *v = list_head(&graph_adjlists(bfs_graph)); v != NULL; v = list_next(v))
    {
        AdjList *adjlist = (AdjList *)list_data(v);
        BfsVertex *vertex = adjlist->vertex;
        Set adj = (Set)(adjlist->adjacent);
        printf("Vertex %d:   ", *((int *)vertex->data));
        for(ListElement *s = list_head(&adj); s != NULL; s = list_next(s))
        {
            BfsVertex *adj_vertex = list_data(s);
            printf("%d  ", *((int *)adj_vertex->data));
        }
        printf("\n");
    }
    printf("\n");

    /* Run BFS */
    bfs(bfs_graph, bfs_start, bfs_vertices);

    /* Print list of vertices */
    printf("List of (Vertex, Hops) reachable from %d:  ", *((int *)bfs_start->data));
    for(ListElement *v = list_head(bfs_vertices); v != NULL; v = list_next(v))
    {
        BfsVertex *vertex = list_data(v);
        printf("(%d, %d) ", *((int *)vertex->data), vertex->hops);
    }
    printf("\n\n\n");
        

    /*
    *************************
            DFS Graph
    *************************
    */
    
    /* Create graph */
    Graph *dfs_graph = malloc(sizeof(*dfs_graph)); 
    if(dfs_graph == NULL)
        return -1;
    graph_init(dfs_graph, dfs_match, NULL);

    /* Insert vertices and edges */
    for(int i = 0; i < 6; i++)
    {
        dfs_data[i].data = &data[i];
        dfs_data[i].color = white;
        graph_insert_vertex(dfs_graph, (void *)&dfs_data[i]);
    }
    graph_insert_edge(dfs_graph, (void *)&dfs_data[0], (void *)&dfs_data[1]);
    graph_insert_edge(dfs_graph, (void *)&dfs_data[0], (void *)&dfs_data[3]);
    graph_insert_edge(dfs_graph, (void *)&dfs_data[1], (void *)&dfs_data[1]);
    graph_insert_edge(dfs_graph, (void *)&dfs_data[2], (void *)&dfs_data[4]);
    graph_insert_edge(dfs_graph, (void *)&dfs_data[4], (void *)&dfs_data[2]);
    graph_insert_edge(dfs_graph, (void *)&dfs_data[1], (void *)&dfs_data[2]);

    /* Select a start vertex */
    AdjList *dfs_adj;
    graph_adjlist(dfs_graph, (void *)&dfs_data[0], &dfs_adj);
    DfsVertex *dfs_start = dfs_adj->vertex;
    
    /* Create list to hold output vertices (and their hops) */
    List *dfs_vertices = malloc(sizeof(*dfs_vertices));
    list_init(dfs_vertices, NULL);
    
    /* Print graph */
    printf("---- DFS Graph ----\n");
    printf("vcount = %d    ecount = %d\n", graph_vcount(dfs_graph), graph_ecount(dfs_graph));
    for(ListElement *v = list_head(&graph_adjlists(dfs_graph)); v != NULL; v = list_next(v))
    {
        AdjList *adjlist = (AdjList *)list_data(v);
        DfsVertex *vertex = adjlist->vertex;
        Set adj = (Set)(adjlist->adjacent);
        printf("Vertex %d:   ", *((int *)vertex->data));
        for(ListElement *s = list_head(&adj); s != NULL; s = list_next(s))
        {
            DfsVertex *adj_vertex = list_data(s);
            printf("%d  ", *((int *)adj_vertex->data));
        }
        printf("\n");
    }
    printf("\n");

    /* Run DFS */
    dfs(dfs_graph, dfs_start, dfs_vertices);

    /* Print list of vertices */
    printf("List of Vertex reachable from %d:  ", *((int *)dfs_start->data));
    for(ListElement *v = list_head(dfs_vertices); v != NULL; v = list_next(v))
    {
        DfsVertex *vertex = list_data(v);
        printf("%d ", *((int *)vertex->data));
    }
    printf("\n");
    
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

int bfs_match(const void *key1, const void *key2)
{
    int *data1 = (int *)((BfsVertex *)key1)->data;
    int *data2 = (int *)((BfsVertex *)key2)->data;

    return match((void *)&data1, (void *)&data2);
}

int dfs_match(const void *key1, const void *key2)
{
    int *data1 = (int *)((DfsVertex *)key1)->data;
    int *data2 = (int *)((DfsVertex *)key2)->data;

    return match((void *)data1, (void *)data2);
}


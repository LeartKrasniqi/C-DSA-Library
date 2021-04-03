/* Implementation of  Graph Searching Methods */

#include "graph_search.h"
#include <stdio.h>

/* Breadth-First Search */
int bfs(Graph *graph, BfsVertex *start, List *hops)
{
    /* Initialize vertices in graph */
    for(ListElement *v = list_head(&graph_adjlists(graph)); v != NULL; v = list_next(v))
    {
        /* Obtain the current vertex (which should be a BfsVertex) */
        BfsVertex *vertex = ((AdjList *)list_data(v))->vertex;
        
        /* Initialize start vertex */
        if(graph->match((void *)vertex, (void *)start))
        {
            vertex->color = gray;
            vertex->hops = 0;
        }
        /* Otherwise, initialize non-start vertex */
        else
        {
            vertex->color = white;
            vertex->hops = -1;
        }
    }

    /* Initialize a queue which will hold the adjacency-list of the start vertex */
    Queue queue;
    queue_init(&queue, NULL);
    AdjList *start_adjlist;
    
    /* Obtain the adjacency-list and return error if unsuccessful */
    if(graph_adjlist(graph, start, &start_adjlist) != 0)
    {
        queue_destroy(&queue);
        return -1;
    }

    /* Push the adjacency-list into the queue */
    if(queue_push(&queue, (void *)start_adjlist) != 0)
    {
        queue_destroy(&queue);
        return -1;
    }

    /* Perform breadth-first search */
    while(queue_size(&queue) > 0)
    {
        /* Get adjlist at front of queue */
        AdjList *adjlist = queue_peek(&queue);

        /* Traverse each vertex in adjlist */
        for(ListElement *v = list_head(&adjlist->adjacent); v != NULL; v = list_next(v))
        {
            BfsVertex *adj_vertex = list_data(v);
            
            /* Get the adjacency-list of the adjacent vertex */
            AdjList *adj_adjlist;
            if(graph_adjlist(graph, adj_vertex, &adj_adjlist) != 0)
            {
                queue_destroy(&queue);
                return -1;
            }

            /* Obtain the ACTUAL adjacent vertex (which is found in the adj_adjlist struct) */
            adj_vertex = adj_adjlist->vertex;

            /* Check color -- white indicates that this vertex has not been visited yet */ 
            if(adj_vertex->color == white)
            {
                /* We have visited it, so change color to gray */
                adj_vertex->color = gray;

                /* Set the number of hops from the start vertex */
                adj_vertex->hops = ((BfsVertex *)adjlist->vertex)->hops + 1;

                /* Push the adjacency-list of this (now visited) vertex into the queue */
                if(queue_push(&queue, adj_adjlist) != 0)
                {
                    queue_destroy(&queue);
                    return -1;
                }
            }
        }

        /* Now, we are done with the adjlist at front of queue, so pop it and mark its vertex as visited */
        if(queue_pop(&queue, (void **)&adjlist) == 0)
            ((BfsVertex *)adjlist->vertex)->color = black;
        else
        {
            queue_destroy(&queue);
            return -1;
        }
    }

    /* We are done with the queue, so can destroy it now */
    queue_destroy(&queue);

    /* Initialize the list which will hold the vertices with hop counts */
    list_init(hops, NULL);
    
    /* Traverse each vertex in graph and insert it into the hops list if hop count is not -1 */
    for(ListElement *v = list_head(&graph_adjlists(graph)); v != NULL; v = list_next(v))
    {
        BfsVertex *vertex = ((AdjList *)list_data(v))->vertex;
        
        /* Only care about visited vertices (i.e., vertices with hops != -1) */
        if(vertex->hops != -1)
        {
            /* Insert vertex into list */
            if(list_insert_next(hops, list_tail(hops), (void *)vertex) != 0)
            {
                list_destroy(hops);
                return -1;
            }
        }
    }

    /* If we get here, hops now contains a list of vertices (along with their hop counts) that can be reached from the start vertex */
    return 0;
} 

/* Depth-First Search */
int dfs(Graph *graph, DfsVertex *start, List *ordered)
{
    /* Mark start vertex as gray (i.e., visited) and obtain its adjacency list */
    start->color = gray;
    AdjList *start_adjlist; 
    if(graph_adjlist(graph, start, &start_adjlist) != 0)
        return -1;

    /* Traverse adjacency-list of start */
    for(ListElement *v = list_head(&start_adjlist->adjacent); v != NULL; v = list_next(v))
    {
        /* Obtain next adjacent vertex and its adjacency-list */
        DfsVertex *adj_vertex = list_data(v);
        AdjList *adj_adjlist;
        if(graph_adjlist(graph, adj_vertex, &adj_adjlist) != 0)
            return -1;
        
        /* Obtain the ACTUAL adjacent vertex (which is found in the adj_adjlist struct) */
        adj_vertex = adj_adjlist->vertex;

        /* If the color of this vertex is white, move one vertex deeper */
        if(adj_vertex->color == white)
            if(dfs(graph, adj_vertex, ordered) != 0)
                return -1;
    }

    /* Now, color the start (i.e., current) vertex black and make it first in the list */
    start->color = black;
    if(list_insert_next(ordered, NULL, (void *)start) != 0)
        return -1;

    /* If we get here, ordered contains a list of topologically-sorted vertices reachable from start */
    return 0;
}



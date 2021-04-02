/* Implementation of Graphs */
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"
#include "set.h"


/* Initialize a graph */
void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    /* Initialize vertices, edges, and functions */
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;

    /* Initialize the list of adjacency-lists */
    list_init(&graph->adjlists, NULL);
}


/* Destroy a graph */
void graph_destroy(Graph *graph)
{
    /* Loop through each adjacency-list in the graph */
    while(list_size(&graph->adjlists) > 0)
    {
        /* Will be used to hold the adjacency-list to be deleted */
        AdjList *adjlist;

        /* Remove the adjacency-list from list of adjacency-lists */ 
        if(list_remove_next(&graph->adjlists, NULL, (void **)&adjlist) == 0)
        {
            set_destroy(&adjlist->adjacent);
            if(graph->destroy != NULL)
                graph->destroy(adjlist->vertex);
            free(adjlist);
        }
    }

    /* The list of adjacency-lists is now empty, so destroy it */
    list_destroy(&graph->adjlists);

    /* To be safe, clear the structure */
    memset(graph, 0, sizeof(Graph));
}


/* Insert a vertex into graph */
int graph_insert_vertex(Graph *graph, const void *data)
{
    /* Do not allow insertion of duplicate vertices */
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
        if(graph->match(data, ((AdjList *)list_data(v))->vertex))
            return 1;

    /* Create the adjacency-list for the vertex */
    AdjList *adjlist = malloc(sizeof(*adjlist));
    if(adjlist == NULL)
        return -1;
    adjlist->vertex = (void *)data;
    set_init(&adjlist->adjacent, graph->match, NULL);

    /* Insert the adjacency-list into the list of adjacency-lists in the graph */
    int retval = list_insert_next(&graph->adjlists, list_tail(&graph->adjlists), adjlist);
    if(retval != 0)
        return retval;

    /* Update the vertex count */
    graph->vcount += 1;

    return 0;
}


/* Insert an edge into graph (From data1 to data2) */
int graph_insert_edge(Graph *graph, const void *data1, const void *data2)
{ 
        
    /* Make sure vertex1 exists in graph (and save it) */
    ListElement *vertex1;
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
    {
        /* If we have a match, vertex1 exists, so save it */
        if(graph->match(data1, ((AdjList *)list_data(v))->vertex))
        {
            vertex1 = v;
            break;
        }

        /* If next element is NULL, we have reached end of list so vertex1 does not exist */
        if(list_next(v) == NULL)
            return -1;
    }

    /* Make sure vertex2 exists in graph */
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
    {
        /* If we have a match, vertex2 exists */
        if(graph->match(data2, ((AdjList *)list_data(v))->vertex))
            break;

        /* If next element is NULL, we have reached end of list so vertex2 does not exist */
        if(list_next(v) == NULL)
            return -1;
    }

    /* Insert vertex2 into the adjacency-list of vertex1 */
    int retval = set_insert(&((AdjList *)list_data(vertex1))->adjacent, data2);
    if(retval != 0)
        return retval;

    /* Update the number of edges */
    graph->ecount += 1;

    return 0;
}


/* Remove a vertex from graph */
int graph_remove_vertex(Graph *graph, void **data)
{
    /* Helper variables */
    ListElement *vertex;        /* Points to vertex to be removed */
    ListElement *prev = NULL;   /* Points to vertex just before vertex to be removed */
    int found = 0;              /* Flag to mark if vertex was found */

    
    /* Traverse each adjacency-list and the vertices it contains */
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
    {
        /* If vertex to be removed is in an adjacency-list, cannot remove it */
        if(set_is_element(&((AdjList *)list_data(v))->adjacent, *data))
            return -1;
        
        /* Check that vertex exists and if so, save it */
        if(graph->match(*data, ((AdjList *)list_data(v))->vertex))
        {
            vertex = v;
            found = 1;
        }
        /* Otherwise, update prev */
        else
            prev = v;
    }

    /* If vertex was never found, return error */
    if(!found)
        return -1;

    /* If vertex has non-empty adjacency-list, cannot remove it */
    if(set_size(&((AdjList *)list_data(vertex))->adjacent) > 0)
        return -1;

    /* Now, remove the vertex */
    AdjList *adjlist;
    if(list_remove_next(&graph->adjlists, prev, (void **)&adjlist) != 0)
        return -1;

    /* Save the vertex data and free the storage associated with the AdjList struct */
    *data = adjlist->vertex;
    free(adjlist);

    /* Updated the number of vertices */
    graph->vcount -= 1;

    return 0;
}


/* Remove an edge from graph */
int graph_remove_edge(Graph *graph, void *data1, void **data2)
{
    /* Find the first vertex */
    ListElement *vertex1 = NULL;
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
    {
        if(graph->match(data1, ((AdjList *)list_data(v))->vertex))
        {
            vertex1 = v;
            break;
        }

        /* If next element is NULL, then the vertex does not exist */
        if(list_next(v) == NULL)
            return -1;
    }

    /* Remove second vertex from adjacency-list of first vertex */
    if(set_remove(&((AdjList *)list_data(vertex1))->adjacent, data2) != 0)
        return -1;

    /* Update the number of edges */
    graph->ecount -= 1;

    return 0;
}


/* Retrieve adjacency-list of a specified vertex */
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist)
{
    /* Obtain the vertex itself */
    ListElement *vertex = NULL;
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
    {
        if(graph->match(data, ((AdjList *)list_data(v))->vertex))
        {
            vertex = v;
            break;
        }

        /* If next element is NULL, then the vertex does not exist */
        if(list_next(v) == NULL)
            return -1;
    }

    /* Pass back the adjacency-list */
    *adjlist = list_data(vertex);

    return 0;
}


/* Check if vertex is adjacent to another */
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2)
{
    /* Obtain the first vertex */
    ListElement *vertex1 = NULL;
    for(ListElement *v = list_head(&graph->adjlists); v != NULL; v = list_next(v))
    {
        if(graph->match(data1, ((AdjList *)list_data(v))->vertex))
        {
            vertex1 = v;
            break;
        }

        /* If next element is NULL, then the vertex does not exist */
        if(list_next(v) == NULL)
            return -1;
    }

    /* Return whether second vertex is in adjacency-list of first vertex */
    return set_is_element(&((AdjList *)list_data(vertex1))->adjacent, data2);
}


/* Example of Topological Sort using DFS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_search.h"

/* Example will deal with courses and their prereqs
    MA111 has no prereqs
    MA112 requires MA111
    EE160 has no prereqs
    EE357 requires ECE160
    EE466 requires ECE160 and MA112
    EE499 requires EE357 and EE357
    EE150 has no prereqs

    Here's what the graph looks like:

    MA111    --- EE160      EE150  
      |      |     |
      V      |     V
    MA112    |   EE357
      |      |     |
      V      |     V
    ECE466 <--   EE499
      |            ^
      |            |
      --------------


    Ideally, we'll get something like this in the end:
                                    
                                  ------------------
                                  |                |
                                  |                V
     MA111 --> MA112  EE160 --> EE466  EE357 --> EE499   EE150
                 |      |         ^      ^
                 |      |         |      |
                 ------------------      |
                        |                |
                        ------------------
*/

int topological_sort(Graph *graph, List *ordered)
{
    /* Initialize list */
    list_init(ordered, NULL);

    /* Loop through every component of graph */
    for(ListElement *v = list_head(&graph_adjlists(graph)); v != NULL; v = list_next(v))
    {
        DfsVertex *vertex = ((AdjList *)list_data(v))->vertex;
        
        /* Run DFS on non-visited components of graph */
        if(vertex->color == white)
        {
            if(dfs(graph, vertex, ordered) != 0)
            {
                list_destroy(ordered);
                return -1;
            }
        }
    }

    return 0;
}

int match(const void *key1, const void *key2)
{
    char *class_name1 = (char *)((DfsVertex *)key1)->data;
    char *class_name2 = (char *)((DfsVertex *)key2)->data;

    if(strcmp(class_name1, class_name2) == 0)
        return 1;
    else
        return 0;
}

int main()
{
    /* Create graph */
    Graph *graph = malloc(sizeof(*graph));
    if(graph == NULL)
        return -1;
    graph_init(graph, match, NULL);

    /* Add the classes as vertices */
    char *classes[7] = {"MA111", "MA112", "EE150", "EE160", "EE357", "EE466", "EE499"};
    BfsVertex *data = malloc(7 * sizeof(*data));
    for(int i = 0; i < 7; i++)
    {
        data[i].data = classes[i];
        data[i].color = white;
        graph_insert_vertex(graph, (void *)&data[i]);
    }

    /* Create the edges */
    graph_insert_edge(graph, (void *)&data[1], (void *)&data[0]);
    graph_insert_edge(graph, (void *)&data[3], (void *)&data[1]);
    graph_insert_edge(graph, (void *)&data[4], (void *)&data[2]);
    graph_insert_edge(graph, (void *)&data[5], (void *)&data[3]);
    graph_insert_edge(graph, (void *)&data[5], (void *)&data[4]);
    graph_insert_edge(graph, (void *)&data[3], (void *)&data[2]);

    /* Allocate List which will contain topologically-ordered classes */
    List *ordered = malloc(sizeof(*ordered));

    /* Run topological sort */
    if(topological_sort(graph, ordered) != 0)
        return -1;
    
    /* Since topological sort gets the vertices in reverse order, reverse the list */
    ListElement *curr = list_head(ordered), *prev = NULL, *next = NULL;
    while(curr != NULL)
    {
        next = list_next(curr);
        list_next(curr) = prev;
        prev = curr;
        curr = next;
    }
    list_head(ordered) = prev;

    /* Print out the ordered list */
    printf("Courses:\n");
    printf("MA111    --- EE160      EE150\n");
    printf("  |      |     |             \n");
    printf("  V      |     V             \n");
    printf("MA112    |   EE357           \n");
    printf("  |      |     |             \n");
    printf("  V      |     V             \n");
    printf("ECE466 <--   EE499           \n");
    printf("  |            ^             \n");
    printf("  |            |             \n");
    printf("  --------------             \n");
    
    printf("\nTopologically Sorted:  ");
    for(ListElement *v = list_head(ordered); v != NULL; v = list_next(v))
    {
        DfsVertex *vertex = list_data(v);
        printf("%s  ", (char *)vertex->data);
    }
    printf("\n");
}


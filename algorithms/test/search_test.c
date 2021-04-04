/* Test the Searching Methods */
#include <stdio.h>
#include <stdlib.h>

#include "search.h"
#include "sort.h"

/* Tree Traverse */
void tree_traverse_test();
void tree_helper(BiTree *tree, int *data);
void print_tree(BiTree *tree);
void print_node(BiTreeNode *n, int level);
void print_list(List *list, char *name);

/* Graph Search */
void graph_search_test();
int match(const void *key1, const void *key2);
int bfs_match(const void *key1, const void *key2);
int dfs_match(const void *key1, const void *key2);

/* Binary Search */
void binary_search_test();
int compare(const void *key1, const void *key2);

int main()
{
    /* Run the tests */
    printf("-------------------- TREE TRAVERSE TEST START --------------------\n");
    tree_traverse_test();
    printf("-------------------- TREE TRAVERSE TEST END --------------------\n\n\n");
    printf("-------------------- GRAPH SEARCH TEST START --------------------\n");
    graph_search_test();
    printf("-------------------- GRAPH SEARCH TEST END --------------------\n\n\n");
    printf("-------------------- BINARY SEARCH TEST START --------------------\n");
    binary_search_test();
    printf("-------------------- BINARY SEARCH TEST END --------------------\n\n");
    return 0;
}


/*
*****************************
        Tree Traverse
*****************************
*/
void tree_traverse_test()
{
    printf("---------- TREE TRAVERSE TEST START ----------\n");
    /* Create a binary tree and insert some ints into it */
    BiTree *left = malloc(sizeof(*left));
    int data1[] = {2,4,5};
    tree_helper(left, data1);
    BiTree *right = malloc(sizeof(*right));
    int data2[] = {3,6,7};
    tree_helper(right, data2);
    BiTree *tree = malloc(sizeof(*tree));
    int data0 = 0;
    bitree_merge(tree, left, right, (void *)&data0);

    /* Print the tree */
    print_tree(tree);

    /* Perform each of the traversals */
    List *preorder_list = malloc(sizeof(List)),
         *inorder_list = malloc(sizeof(List)),
         *postorder_list = malloc(sizeof(List));
    list_init(preorder_list, NULL);
    list_init(inorder_list, NULL);
    list_init(postorder_list, NULL);
    preorder(bitree_root(tree), preorder_list);
    inorder(bitree_root(tree), inorder_list);
    postorder(bitree_root(tree), postorder_list);

    /* Print out the lists */
    print_list(preorder_list, "Preorder");
    print_list(inorder_list, "Inorder");
    print_list(postorder_list, "Postorder");

    printf("---------- TREE TRAVERSE TEST END ----------\n\n");

}

void tree_helper(BiTree *tree, int *data)
{
    bitree_init(tree, NULL);
    bitree_insert_left(tree, NULL, (void *)&data[0]);
    bitree_insert_left(tree, bitree_root(tree), (void *)&data[1]);
    bitree_insert_right(tree, bitree_root(tree), (void *)&data[2]);
}

void print_tree(BiTree *tree)
{
    printf("Size: %d\n", bitree_size(tree));
    print_node(bitree_root(tree), 0);
}

void print_node(BiTreeNode *n, int level)
{
    if(bitree_is_eob(n))
        return;

    /* Pretty-print */
    for(int i = 0; i < level; i++)
        printf("  ");

    /* Print out contents of node */
    int data = *((int *)bitree_data(n));
    printf("%d\n", data);

    /* Print out left and right children */
    print_node(bitree_left(n), level + 1);
    print_node(bitree_right(n), level + 1);
}

void print_list(List *list, char *name)
{
    printf("List: %s, Size: %d, Contents: ", name, list_size(list));
    for(ListElement *e = list_head(list); e != NULL; e = list_next(e))
    {
        int data = *((int *)list_data(e));
        printf("%d  ", data);
    }
    printf("\n");
}



/*
****************************
        Graph Search
****************************
*/

void graph_search_test()
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
        return;
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
    printf("\n\n");


    /*
    *************************
            DFS Graph
    *************************
    */

    /* Create graph */
    Graph *dfs_graph = malloc(sizeof(*dfs_graph));
    if(dfs_graph == NULL)
        return;
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




/*
*****************************
        Binary Search
*****************************
*/

void binary_search_test()
{
    /* Create an array of random values */
    int data[20];
    srand(time(NULL));
    for(int i = 0; i < 20; i++)
        data[i] = rand() % 100;

    /* Pick some desired elements */
    int desired[4] = {data[6], data[15], data[0], 100};

    /* Sort the array */
    insertion_sort(data, 20, sizeof(int), compare);

    /* Find the desired elements */
    int indices[4];
    for(int i = 0; i < 4; i++)
        indices[i] = binary_search(data, &desired[i], 20, sizeof(int), compare);

    /* Print out the results */
    printf("Data: "); 
    for(int i = 0; i < 20; i++) 
        printf("%d  ", data[i]);
    printf("\n");
    for(int i = 0; i < 4; i++)
        printf("Desired: %d  Index: %d\n", desired[i], indices[i]);

}

int compare(const void *key1, const void *key2)
{
    int val1 = *((int *)key1);
    int val2 = *((int *)key2);

    if(val1 > val2)
        return 1;
    else if(val1 < val2)
        return -1;
    else
        return 0;
}

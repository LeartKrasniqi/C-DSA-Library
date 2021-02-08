/* Test of Heap Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void print_heap(Heap *h);
int compare(const void *key1, const void *key2);

typedef struct Data_ {
    int value;
    char *char_value;
} Data;

/* Testing the following methods and macros:
    Methods:
      - heap_init()
      - heap_destroy()
      - heap_insert()
      - heap_extract()
    Macros:
      - heap_size()
*/
int main()
{
    /* Allocate memory for the Heap structure and initialize */
    Heap *heap = malloc(sizeof(*heap));
    if(heap == NULL)
        return -1;
    heap_init(heap, compare, NULL);

    /* Create some data ojects and insert them into the heap */
    char *strings[10] = {"zero", "one", "two", "three", "four", 
                         "five", "six", "seven", "eight", "nine"};
    Data *elements[10];
    for(int i = 0; i < 10; i++)
    {
        elements[i] = malloc(sizeof(*elements));
        elements[i]->value = i;
        elements[i]->char_value = strings[i]; 
        heap_insert(heap, (void *)elements[i]);
    }

    /* Print out the heap */
    printf("---- Inserted into Heap ----\n");
    print_heap(heap);
    printf("\n");

    /* Extract the top element a few times and print */
    printf("---- Extracting from Heap ----\n");
    Data *d[10];
    for(int i = 0; i < 10; i++)
    {
        d[i] = malloc(sizeof(*d));
        if(heap_extract(heap, (void *)&d[i]) == 0)
            printf("Extracted top element:  (%d, %s)\n", d[i]->value, d[i]->char_value);
    }
    print_heap(heap);
    printf("\n");

    /* Destroy the heap */
    heap_destroy(heap);

    return 0;
}

/* Compare for a top-heavy heap */
int compare(const void *key1, const void *key2)
{
    int val1 = ((Data *)key1)->value;
    int val2 = ((Data *)key2)->value;

    if(val1 > val2)
        return 1;
    else if(val1 == val2)
        return 0;
    else
        return -1;
}

/* Print out the heap */
void print_heap(Heap *heap)
{
    printf("Size: %d\n", heap_size(heap));
    for(int i = 0; i < heap_size(heap); i++)
    {
        Data *data = (Data *)heap->tree[i];
        printf("(%d, %s)\n", data->value, data->char_value);
    }
}
    


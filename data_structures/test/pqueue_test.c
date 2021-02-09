/* Test of PQueue Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"

void print_pqueue(PQueue *p);
int compare(const void *key1, const void *key2);

typedef struct Data_ {
    int value;
    char *char_value;
} Data;

/* Testing the following methods and macros:
    Methods:
      - pqueue_init()
      - pqueue_destroy()
      - pqueue_insert()
      - pqueue_extract()
    Macros:
      - pqueue_size()
      - pqueue_peek()

    Note:
      - PQueues are really just heaps, so the tests are pretty much the same
*/
int main()
{
    /* Allocate memory for the PQueue structure and initialize */
    PQueue *pqueue = malloc(sizeof(*pqueue));
    if(pqueue == NULL)
        return -1;
    pqueue_init(pqueue, compare, NULL);

    /* Create some data ojects and insert them into the pqueue */
    char *strings[10] = {"zero", "one", "two", "three", "four", 
                         "five", "six", "seven", "eight", "nine"};
    Data *elements[10];
    for(int i = 0; i < 10; i++)
    {
        elements[i] = malloc(sizeof(*elements));
        elements[i]->value = i;
        elements[i]->char_value = strings[i]; 
        pqueue_insert(pqueue, (void *)elements[i]);
    }

    /* Print out the pqueue */
    printf("---- Inserted into PQueue ----\n");
    print_pqueue(pqueue);
    printf("\n");

    /* Peek at and extract the top element a few times and print */
    printf("---- Extracting from PQueue ----\n");
    Data *d[10];
    for(int i = 0; i < 10; i++)
    {
        Data *dd = pqueue_peek(pqueue);
        if(dd != NULL)
            printf("Peeking at top element: (%d, %s)\n", dd->value, dd->char_value);

        d[i] = malloc(sizeof(*d));
        if(pqueue_extract(pqueue, (void *)&d[i]) == 0)
            printf("Extracted top element:  (%d, %s)\n", d[i]->value, d[i]->char_value);
    }
    print_pqueue(pqueue);
    printf("\n");

    /* Destroy the pqueue */
    pqueue_destroy(pqueue);

    return 0;
}

/* Compare for a top-heavy pqueue */
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

/* Print out the pqueue */
void print_pqueue(PQueue *pqueue)
{
    printf("Size: %d\n", pqueue_size(pqueue));
    for(int i = 0; i < pqueue_size(pqueue); i++)
    {
        Data *data = (Data *)pqueue->tree[i];
        printf("(%d, %s)\n", data->value, data->char_value);
    }
}
    


/* Test of Chained Hash Table Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "chtbl.h"

void print_table(CHTbl *t);
int hash(const void *key);
int match(const void *key1, const void *key2);

/* Testing methods and macros:
    Methods:
      - chtbl_init()
      - chtbl_destroy()
      - chtbl_insert()
      - chtbl_remove()
      - chtbl_lookup()
    Macros:
      - chtbl_size()
*/
int main()
{
    /* Allocate memory for CHTbl */
    CHTbl *table = malloc(sizeof(*table));
    if(table == NULL)
        return -1;

    /* Initialize table */
    int buckets = 5;
    if(chtbl_init(table, buckets, hash, match, NULL) != 0)
        return -1;

    /* Insert some data */
    int arr[30];
    for(int i = 0; i < 30; i++)
    {
        arr[i] = i;
        chtbl_insert(table, (void *)&arr[i]);
    }
    printf("--- Inserted Data ---\n");
    print_table(table);
    printf("\n");

    /* Lookup some data */
    int lookup[3] = {4, 18, 100};
    printf("--- Lookup Data ---\n");
    for(int i = 0; i < 3; i++)
    {
        int data = lookup[i];
        int *temp = &data;
        printf("Looking for %d:  %s\n", lookup[i], chtbl_lookup(table, (void *)&temp) == 0 ? "Found!" : "Not Found");
    }
    printf("\n");

    /* Remove some data */
    int remove[3] = {0, 10, 27};
    printf("--- Remove Data ---\n");
    for(int i = 0; i < 3; i++)
    {
        int data = remove[i];
        int *temp = &data;
        if(chtbl_remove(table, (void *)&temp) == 0)
            printf("Removed %d\n", *temp);
    }
    print_table(table);
    printf("\n");

    /* Destroy the table */
    chtbl_destroy(table);

    return 0;
}

/* Function to print out the table */
void print_table(CHTbl *t)
{
    printf("Size of Table: %d\n", chtbl_size(t));
    for(int i = 0; i < t->buckets; i++)
    {
        List *bucket_list = &t->table[i];
        printf("Bucket %d: ", i);
        for(ListElement *e = list_head(bucket_list); e != NULL; e = list_next(e))
        {
            int *data = (int *)list_data(e);
            printf("%d  ", *data);
        }
        printf("\n");
    }
}

/* Hash function -- This is not a good one, just made for ease of testing */
int hash(const void *key)
{
    int retval = *((int *)key);
    return retval;
}

/* Matching function */
int match(const void *key1, const void *key2)
{
    int val1 = *((int *)key1);
    int val2 = *((int *)key2);
    return val1 == val2 ? 1 : 0;
}


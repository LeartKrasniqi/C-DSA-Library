/* Testing Open Addressed Hash Table Implementation */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

void print_table(OHTbl *t);
int h1(const void *key);
int h2(const void *key);
int match(const void *key1, const void *key2);

/* Testing methods and macros:
    Methods:
      - ohtbl_init()
      - ohtbl_destroy()
      - ohtbl_insert()
      - ohtbl_remove()
      - ohtbl_lookup()
    Macros:
      - ohtbl_size()
*/
int main()
{
    /* Allocate memory for OHTbl */
    OHTbl *table = malloc(sizeof(*table));
    if(table == NULL)
        return -1;

    /* Initialize table */
    int positions = 13;
    if(ohtbl_init(table, positions, h1, h2, match, NULL) != 0)
        return -1;
    
    /* Insert some data */
    char *names[4] = {"foo", "blah", "randomname1", "randomname200"};
    for(int i = 0; i < 4; i++)
        ohtbl_insert(table, (void *)names[i]);
    printf("--- Inserted Data ---\n");
    print_table(table);
    printf("\n");

    /* Lookup some data */
    char *lookup[3] = {"foo", "bar", "randomname1"};
    for(int i = 0; i < 3; i++)
    {
        char *data = lookup[i]; 
        printf("Looking for %s:  %s\n", lookup[i], ohtbl_lookup(table, (void *)&data) == 0 ? "Found!" : "Not Found");
    }
    printf("\n");

    /* Remove some data */
    char *remove[2] = {"foo", "randomname2"};
    printf("--- Remove Data ---\n");
    for(int i = 0; i < 2; i++)
    {
        char *data = remove[i];
        if(ohtbl_remove(table, (void *)&data) == 0)
            printf("Removed %s\n", data);
    }
    print_table(table);
    printf("\n");

    /* Destroy the table */
    ohtbl_destroy(table);

    return 0;
}

/* Function to print out table */
void print_table(OHTbl *t)
{
    printf("Size of Table: %d\n", ohtbl_size(t));
    for(int i = 0; i < t->positions; i++)
    {
        printf("Position %d: ", i);
        if(t->table[i])
            printf("%s", (char *)(t->table[i]));
        printf("\n");
    }
}

/* Hash function */
int h1(const void *key)
{
    int retval = strlen((char *)key);
    return retval;
}

/* Second hash function */
int h2(const void *key)
{
    char *str = (char *)key;
    int retval = (int)str[strlen(str) - 1];
    return retval;
}

/* Matching function */
int match(const void *key1, const void *key2)
{
    int strcmp_ret = strcmp((char *)key1, (char *)key2);
    int ret;
    if(strcmp_ret == 0)
        ret = 1;
    else
        ret = 0;
    
    return ret; 
}


    

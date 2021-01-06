/* Test of Set Implementation */
#include <stdio.h>
#include <stdlib.h>

#include "set.h"

typedef struct Number_ {
    int val;
} Number;

void print_set(Set *s, char *name);

/* Function used to compare elements of set */
int match(const void *key1, const void *key2);

/* Function used to help with insert of elements */
int set_insert_helper(Set *set, Number **nums, int start, int end);

/* Testing methods and macros
    Methods:
      - set_init()
      - set_destroy()
      - set_insert()
      - set_remove()
      - set_union()
      - set_insersection()
      - set_difference()
      - set_is_element()
      - set_is_subset()
      - set_is_equal()
    Macros:
      - set_size()

    Notes:
      - Sets are implemented as linked lists
      - All the methods and macros in list.h can be applied here as well
*/
int main()
{
    /* Allocate memory for some sets */
    Set *A = malloc(sizeof(*A));  if(!A) return -1;
    Set *B = malloc(sizeof(*B));  if(!B) return -1;
    Set *C = malloc(sizeof(*C));  if(!C) return -1;
    Set *D = malloc(sizeof(*D));  if(!D) return -1;

    /* Initialize the sets */
    set_init(A, match, NULL);
    set_init(B, match, NULL);
    set_init(C, match, NULL);
    set_init(D, match, NULL);
    
    /* Create some elements */
    Number *nums[10];
    for(int i = 0; i < 10; i++)
    {
        nums[i] = malloc(sizeof(*nums[i]));
        nums[i]->val = i;
    }

    /* Populate the sets */
    set_insert_helper(A, nums, 0, 4);
    set_insert_helper(B, nums, 3, 6);
    set_insert_helper(C, nums, 0, 10);
    set_insert_helper(D, nums, 8, 9);
    printf("--- Inserted Elements into Set ---\n");
    print_set(A, "A");
    print_set(B, "B");
    print_set(C, "C");
    print_set(D, "D");
    printf("\n");
    
    /* Set union */
    Set *AuB = malloc(sizeof(*AuB));
    set_union(AuB, A, B);
    printf("--- Performed Set Union ---\n");
    print_set(AuB, "A+B");
    printf("\n");

    /* Set intersection */
    Set *AB = malloc(sizeof(*AB));
    set_intersection(AB, A, B);
    printf("--- Performed Set Intersection ---\n");
    print_set(AB, "AB");
    printf("\n");

    /* Set difference */
    Set *DC = malloc(sizeof(*DC));
    set_difference(DC, D, C);
    printf("--- Performed Set Difference --\n");
    print_set(DC, "D-C");
    printf("\n");

    /* Set is element */
    printf("--- Checking if Element is in Set ---\n");
    printf("%d in A? : %s\n", nums[0]->val, set_is_element(A, nums[0]) ? "yes" : "no");
    printf("%d in B? : %s\n", nums[8]->val, set_is_element(B, nums[8]) ? "yes" : "no");
    printf("%d in C? : %s\n", nums[2]->val, set_is_element(C, nums[2]) ? "yes" : "no");
    printf("%d in D? : %s\n", nums[4]->val, set_is_element(D, nums[4]) ? "yes" : "no");
    printf("\n");

    /* Set is subset */
    printf("--- Checking subsets ---\n");
    printf("A is subset of A? : %s\n", set_is_subset(A, A) ? "yes" : "no");
    printf("A is subset of B? : %s\n", set_is_subset(A, B) ? "yes" : "no");
    printf("A is subset of C? : %s\n", set_is_subset(A, C) ? "yes" : "no");
    printf("C is subset of D? : %s\n", set_is_subset(C, D) ? "yes" : "no");
    printf("\n");

    /* Remove an element */
    printf("-- Removing elements ---\n");
    for(int i = 4; i < 10; i++)
        set_remove(C, (void **)&nums[i]);
    print_set(C, "C");
    printf("\n"); 

    /* Set is equal */
    printf("--- Checking set equality ---\n");
    printf("A is equal to A? : %s\n", set_is_equal(A, A) ? "yes" : "no");
    printf("A is equal to C? : %s\n", set_is_equal(A, C) ? "yes" : "no");
    printf("B is equal to D? : %s\n", set_is_equal(B, D) ? "yes" : "no");
    printf("C is equal to B? : %s\n", set_is_equal(C, B) ? "yes" : "no");
    printf("\n");

    /* Destroy the sets */
    set_destroy(A);
    set_destroy(B);
    set_destroy(C);
    set_destroy(D);

    return 0;
}

/* Helper insertion function */
int set_insert_helper(Set *set, Number **nums, int start, int end)
{
    int res;
    for(int i = start; i < end; i++)
    {
        res = set_insert(set, nums[i]);
        if(res == -1)
            return res;
    }
    return res;
}

/* User-defined method to compare elements in set */
int match(const void *key1, const void *key2)
{
    return (((Number *)key1)->val == ((Number *)key2)->val) ? 1 : 0;
}

void print_set(Set *set, char *name)
{
    printf("Set %s:  Size = %d,  Contents = ", name, set_size(set));
    for(ListElement *e = list_head(set); e != NULL; e = list_next(e))
    {
        Number *n = (Number *)list_data(e);
        printf("%d  ", n->val);
    }
    printf("\n");
}


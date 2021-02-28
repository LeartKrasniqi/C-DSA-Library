/* Example of Sets: Set Covering */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "set.h"

/* Idea:
    Set S = {A1, A2, ... , An} --> Universe
    P = collection of m sets whose union equals S
    A subset of P, called C, covers S if the union of the sets in C equals S
   

   Goal: Find the smallest such C


   Example:
    S = {1,2,3,4,5}
    P = { {1,2,3}, {2,4}, {3,4}, {4,5} }
    
    Clearly, ({1,2,3} U {2,4} U {3,4} U {4,5}) = S
    But we can cover S with a smaller set C:
    C = { {1,2,3}, {4,5} }
*/


/* Structure for subsets identified by a key */
typedef struct KSet_ {
    void *key;
    Set set;
} KSet;

/* Perform the set covering algorithm */
int cover(Set *members, Set *subsets, Set *covering)
{
    /* Initialize the covering */
    set_init(covering, subsets->match, NULL);

    /* Store the max member in the set */
    ListElement *max_member;

    /* While there are non-covered members and candidate subsets */
    while( (set_size(members) > 0) && (set_size(subsets) > 0) )
    {
        /* Find the subset that covers the most members */
        int max_size = 0;
        Set intersection;
        for(ListElement *member = list_head(subsets); member != NULL; member = list_next(member))
        {
            /* Obtain intersection */
            if(set_intersection(&intersection, &((KSet *)list_data(member))->set, members) != 0)
               return -1;

            /* If the size of this intersection is greater than the current max_size, save it and the current member */
            if(set_size(&intersection) > max_size)
            {
                max_member = member;
                max_size = set_size(&intersection);
            }

            /* Cleanup */
            set_destroy(&intersection);
        }

        /* If there was no intersection, a covering is not possible */
        if(max_size == 0)
            return 1;

        /* Insert the selected subset into the covering */
        KSet *subset = (KSet *)list_data(max_member);
        if(set_insert(covering, subset) != 0)
            return -1;

        /* Remove each covered member from the set of non-covered members */
        for(ListElement *member = list_head(&((KSet *)list_data(max_member))->set); member != NULL; member = list_next(member))
        {
            void *data = list_data(member);
            if( (set_remove(members, (void **)&data) == 0) && (members->destroy != NULL) )
                members->destroy(data);
        }

        /* Remove the subset from the set of candidate subsets */
        if(set_remove(subsets, (void **)&subset) != 0)
            return -1;
    }

    /* If there are still non-covered members, no covering is possible */
    if(set_size(members) > 0)
        return -1;

    /* If we get here, we obtained a covering */
    return 0;
}

int match(const void *key1, const void *key2)
{
    return *((int *)key1) == *((int *)key2) ? 1 : 0;
}

int match2(const void *key1, const void *key2)
{
    KSet *subset1 = (KSet *)key1;
    KSet *subset2 = (KSet *)key2;
    return set_is_equal(&subset1->set, &subset2->set);
}

void subset_insert_helper(Set *subset, int *vals, int data_size)
{
    for(int i = 0; i < data_size; i++)
    {
        int *data = malloc(sizeof(*data));
        *data = vals[i];
        set_insert(subset, (void *)data);
    }
}

void print_set(Set *set)
{
    for(ListElement *e = list_head(set); e != NULL; e = list_next(e))
    {
        int *n = (int *)list_data(e);
        printf("%d  ", *n);
    }
}

void print_subsets(Set *set, char *name)
{
    printf("Set %s:  Size = %d,  Contents = ", name, set_size(set));
    for(ListElement *e = list_head(set); e != NULL; e = list_next(e))
    {
        KSet *subset = (KSet *)list_data(e);
        printf("{");
        print_set(&subset->set);
        printf("}   ");
    }
    printf("\n");
}

int main()
{
    /* Create the example set: S = {1,2,3,4,5} */
    Set *S = malloc(sizeof(*S));
    set_init(S, match, NULL);
    for(int i = 1; i < 6; i++)
    {
        int *data = malloc(sizeof(*data));
        *data = i;
        if(set_insert(S, (void *)data) != 0)
            return -1;
    }

    /* Create the set of subsets: P = { {1,2,3}, {2,4}, {3,4}, {4,5} } */
    Set *P = malloc(sizeof(*P));
    set_init(P, match2, NULL);
    for(int i = 0; i < 4; i++)
    {
        KSet *k_subset = malloc(sizeof(*k_subset));
        Set *subset = &k_subset->set;
        set_init(subset, match, NULL);
        switch(i)
        {
            case 0:
            {
                int vals[3] = {1,2,3};
                subset_insert_helper(subset, vals, 3); 
                break;
            }
            case 1:
            {
                int vals[2] = {2,4};
                subset_insert_helper(subset, vals, 2); 
                break;
            }
            case 2:
            {
                int vals[2] = {3,4};
                subset_insert_helper(subset, vals, 2); 
                break;
            }
            case 3:
            {
                int vals[2] = {4,5};
                subset_insert_helper(subset, vals, 2); 
                break;
            }
        }
        set_insert(P, (void *)k_subset);
    }

    /* Print out the sets and then the covering */
    printf("Set %s:  Size = %d,  Contents = ", "S", set_size(S));
    print_set(S);
    printf("\n");
    print_subsets(P, "P");

    Set *covering = malloc(sizeof(*covering)); 
    if(cover(S, P, covering) != 0)
    {
        printf("No covering possible!\n");
        return 1;
    }
    print_subsets(covering, "Cover");

    return 0;
}


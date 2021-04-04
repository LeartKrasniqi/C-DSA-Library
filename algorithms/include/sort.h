/* Header for Sorting Algorithms */
#ifndef _SORT_H
#define _SORT_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>


/*
*********************************
        Interface Methods
*********************************
*/

/* Insertion Sort
    @param data       Array of elements
    @param num_elem   Number of elements in data
    @param elem_size  Size of each element (in bytes)
    @param compare    Function used to compare elements

    @return 0 if sorting successful, -1 otherwise

    Notes:
      - For ascending sort, compare should return 1 if key1>key2, 0 if key1=key2, and -1 if key1<key2
      - For descending sort, reverse the above cases returning 1 and -1
      - Upon return, data contains the sorted elements
      - Complexity: O(n^2), where n is the number of elements to be sorted
*/
int insertion_sort(void *data, int num_elem, int elem_size, int (*compare)(const void *key1, const void *key2));


/* Quicksort
    @param data       Array of elements
    @param num_elem   Number of elements in data 
    @param elem_size  Size of each element (in bytes)
    @param compare    Function used to compare elements

    @return 0 if sorting successful, -1 otherwise

    Notes:
      - For ascending sort, compare should return 1 if key1>key2, 0 if key1=key2, and -1 if key1<key2
      - For descending sort, reverse the above cases returning 1 and -1
      - Upon return, data contains the sorted elements
      - Complexity: O(nlog(n)) where n is the number of elements to be sorted
*/
int quick_sort(void *data, int num_elem, int elem_size, int (*compare)(const void *key1, const void *key2));


/* Merge Sort
    @param data       Array of elements
    @param num_elem   Number of elements in data
    @param elem_size  Size of each element (in bytes)
    @param compare    Function used to compare elements
 
    @return 0 if sorting successful, -1 otherwise
    
    Notes:
      - For ascending sort, compare should return 1 if key1>key2, 0 if key1=key2, and -1 if key1<key2
      - For descending sort, reverse the above cases returning 1 and -1
      - Upon return, data contains the sorted elements
      - Complexity: O(nlog(n)) where n is the number of elements to be sorted
*/
int merge_sort(void *data, int num_elem, int elem_size, int (*compare)(const void *key1, const void *key2));


/* Counting Sort
    @param data      Array of ints
    @param num_elem  Number of ints in data
    @param max       Maximum integer in data, plus 1

    @return 0 if sorting successful, -1 otherwise

    Notes:
      - Upon return, data contains the sorted elements
      - Complexity: O(n + k), where n is the number of ints to be sorted and k is the max in the array, plus 1
*/
int counting_sort(int *data, int num_elem, int max);


/* Radix Sort
    @param data      Array of ints
    @param num_elem  Number of ints in data
    @param num_pos   Number of digit positions in each int
    @param radix     Radix (i.e., base) of values in data

    @return 0 if sorting successful, -1 otherwise

    Notes:
      - Makes use of a modified version of counting_sort one digit position at a time
      - Upon return, data contains the sorted elements
      - Complexity: O(pn + pr), where n is the number of ints to be sorted, r is the radix, and p is the number of digit positions
*/
int radix_sort(int *data, int num_elem, int num_pos, int radix);

#endif

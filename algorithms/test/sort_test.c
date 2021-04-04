/* Testing the Sorting Implementation */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

#define N 20

int compare(const void *key1, const void *key2);
int find_max(int *arr);
void print_arr(int *arr);
int is_sorted(int *arr);

int main()
{
    /* Data (Random two-digit numbers) */
    int data[N];
    srand(time(NULL));
    for(int i = 0; i < N; i++)
        data[i] = rand() % 90 + 10;

    /* Arrays for each sorting method */
    int sorted[5][N];
    for(int i = 0; i < 5; i++)
        memcpy(sorted[i], data, N * sizeof(int));

    /* Perform the sorts  */
    insertion_sort(sorted[0], N, sizeof(int), compare);
    quick_sort(sorted[1], N, sizeof(int), 0, N - 1, compare);
    merge_sort(sorted[2], N, sizeof(int), 0, N - 1, compare);
    counting_sort(sorted[3], N, find_max(sorted[3]) + 1);
    radix_sort(sorted[4], N, 2, 10);

    /* Print out the arrays */
    printf("%-17s", "Original: "); print_arr(data); printf("\n");
    printf("%-17s", "Insertion Sort: "); print_arr(sorted[0]); printf("\n");
    printf("%-17s", "Quick Sort: "); print_arr(sorted[1]); printf("\n");
    printf("%-17s", "Merge Sort: "); print_arr(sorted[2]); printf("\n");
    printf("%-17s", "Counting Sort: "); print_arr(sorted[3]); printf("\n");
    printf("%-17s", "Radix Sort: "); print_arr(sorted[4]); printf("\n");

    return 0;
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

int find_max(int *arr)
{
    int max = INT_MIN;
    for(int i = 0; i < N; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}

void print_arr(int *arr)
{
    for(int i = 0; i < N; i++)
        printf("%2d ", arr[i]);
    printf("  ==> %s", is_sorted(arr) ? "SORTED" : "UNSORTED");
}

int is_sorted(int *arr)
{
    for(int i = 0; i < N - 1; i++)
        if(compare(&arr[i], &arr[i+1]) == 1)
            return 0;
    return 1;
}

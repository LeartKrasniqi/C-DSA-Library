/* Implementation of Sorting Methods */
#include "sort.h"


/*
******************************
        Insertion Sort
******************************
*/

/* Perform Insertion Sort */
int insertion_sort(void *data, int num_elem, int elem_size, int (*compare)(const void *key1, const void *key2))
{
    /* Treat data as a char array (and use elem_size to access elements) */
    char *arr = (char *)data; 
    
    /* Allocate storage for a key element */
    void *key = malloc(elem_size);
    if(key == NULL)
        return -1;

    /* Loop through the elements and repeatedly insert a key element among the sorted elements */
    for(int i = 1; i < num_elem; i++)
    {
        /* Copy the element in data into the key element */
        memcpy(key, &arr[i * elem_size], elem_size);

        /* Determine the position where to insert the key element */
        int j = i - 1;
        while( (j >= 0) && (compare(&arr[j * elem_size], key) > 0) )
        {
            memcpy(&arr[(j+1) * elem_size], &arr[j * elem_size], elem_size);
            j--;
        }

        /* Insert the key element */
        memcpy(&arr[(j+1) * elem_size], key, elem_size);
    }

    /* Cleanup */
    free(key);

    return 0;
}




/*
**************************
        Quick Sort
**************************
*/

/* Compare two integers (used for median-of-three partitioning) */
static int quick_sort_compare_int(const void *int1, const void *int2)
{
    int val1 = *((int *)int1);
    int val2 = *((int *)int2);

    if(val1 > val2)
        return 1;
    else if(val1 < val2)
        return -1;
    else
        return 0;
}

/* Perform median-of-three partitioning */
static int quick_sort_partition(void *data, int elem_size, int start_idx, int end_idx, int (*compare)(const void *key1, const void *key2))
{
    /* Treat data as a char array (and use elem_size to access elements) */
    char *arr = (char *)data; 
    
    /* Allocate storage for partion element */
    void *part_elem = malloc(elem_size);
    if(part_elem == NULL)
        return -1;
    
    /* Allocate storage for swapping element */
    void *temp_elem = malloc(elem_size);
    if(temp_elem == NULL)
    {
        free(part_elem);
        return -1;
    }

    /* Get three random indices */
    int random[3];
    random[0] = (rand() % (end_idx - start_idx + 1)) + start_idx;
    random[1] = (rand() % (end_idx - start_idx + 1)) + start_idx;
    random[2] = (rand() % (end_idx - start_idx + 1)) + start_idx;
    
    /* Perform insertion sort to sort the indices */
    insertion_sort(random, 3, sizeof(int), quick_sort_compare_int);

    /* The partition element is the one at the median index */
    memcpy(part_elem, &arr[random[1] * elem_size], elem_size);

    /* Create two partitions around the partition value */
    start_idx--;
    end_idx++;
    while(1)
    {
        /* Move left until an element is found in wrong position */
        do
            end_idx--;
        while(compare(&arr[end_idx * elem_size], part_elem) > 0);

        /* Move right until an element is found in wrong position */
        do
            start_idx++;
        while(compare(&arr[start_idx * elem_size], part_elem) < 0);

        /* If start_idx has reached/surpassed end_idx, break out of loop */
        if(start_idx >= end_idx)
            break;
        /* Otherwise, swap the elements under the two indices */
        else
        {
            memcpy(temp_elem, &arr[start_idx * elem_size], elem_size);
            memcpy(&arr[start_idx * elem_size], &arr[end_idx * elem_size], elem_size);
            memcpy(&arr[end_idx * elem_size], temp_elem, elem_size);
        }
    }

    /* Cleanup */
    free(part_elem);
    free(temp_elem);

    /* Return the position dividing the two partitions */
    return end_idx;
}

/* Perform Quick Sort */
int quick_sort(void *data, int num_elem, int elem_size, int start_idx, int end_idx, int (*compare)(const void *key1, const void *key2))
{
    /* Recurse until not possible to parition any further */
    if(start_idx < end_idx)
    {
        /* Get the partition index */
        int part_idx = quick_sort_partition(data, elem_size, start_idx, end_idx, compare);
        if(part_idx < 0)
            return -1;

        /* Recursively sort the left partition */
        if(quick_sort(data, num_elem, elem_size, start_idx, part_idx, compare) != 0)
            return -1;

        /* Recursively sort the right partition */
        if(quick_sort(data, num_elem, elem_size, part_idx + 1, end_idx, compare) != 0)
            return -1;
    }

    return 0;
}




/*
**************************
        Merge Sort
**************************
*/

/* Perform the merging of sorted arrays into a single array */
static int merge_sort_merge(void *data, int elem_size, int start_idx, int mid_idx, int end_idx, int (*compare)(const void *key1, const void *key2))
{
    /* Treat data as a char array (and use elem_size to access elements) */
    char *arr = (char *)data;

    /* Allocate memory to hold the merged elements */
    char *merged = malloc(elem_size * ((end_idx - start_idx) + 1));
    if(merged == NULL)
        return -1;

    /* Merge counters */
    int left_pos = start_idx;       /* Keep track of sorted left division */
    int right_pos = mid_idx + 1;    /* Keep track of sorted right division */
    int merge_pos = 0;              /* Keep track of position to insert the element in the merged array */
    
    /* Keep merging while either divison has elements to merge */
    while( (left_pos <= mid_idx) || (right_pos <= end_idx) )
    {
        /* Left division has no more elements to merge */
        if(left_pos > mid_idx)
        {
            /* Insert the (already sorted) elements from the right division into the merged array */
            while(right_pos <= end_idx)
            {
                memcpy(&merged[merge_pos * elem_size], &arr[right_pos * elem_size], elem_size);
                right_pos++;
                merge_pos++;
            }
            continue;
        }
        /* Right division has no more elements to merge */
        else if(right_pos > end_idx)
        {
            /* Insert the (already sorted) elements from the left division into the merged array */
            while(left_pos <= mid_idx)
            {
                memcpy(&merged[merge_pos * elem_size], &arr[left_pos * elem_size], elem_size);
                left_pos++;
                merge_pos++;
            }
            continue;
        }

        /* Compare elements at left_pos and right_pos, and insert the proper one into merge_pos of the merged array */
        if(compare(&arr[left_pos * elem_size], &arr[right_pos * elem_size]) < 0)
        {
            memcpy(&merged[merge_pos * elem_size], &arr[left_pos * elem_size], elem_size);
            left_pos++;
            merge_pos++;
        }
        else
        {
            memcpy(&merged[merge_pos * elem_size], &arr[right_pos * elem_size], elem_size);
            right_pos++;
            merge_pos++;
        }
    }

    /* Now, merged contains the sorted array, so copy it back into arr (which points to data) */
    memcpy(&arr[start_idx * elem_size], merged, elem_size * ((end_idx - start_idx) + 1));

    /* Cleanup */
    free(merged);

    return 0;
}  


/* Perform Merge Sort */
int merge_sort(void *data, int num_elem, int elem_size, int start_idx, int end_idx, int (*compare)(const void *key1, const void *key2))
{
    /* Recurse until no more divisions can be made */
    if(start_idx < end_idx)
    {
        /* Determine where to divide the elements */
        int mid_idx = (int)((start_idx + end_idx - 1) / 2);

        /* Recursively sort the left division */
        if(merge_sort(data, num_elem, elem_size, start_idx, mid_idx, compare) != 0)
            return -1;

        /* Recursively sort the right division */
        if(merge_sort(data, num_elem, elem_size, mid_idx + 1, end_idx, compare) != 0)
            return -1;

        /* Now, merge the two sorted divisions into a single sorted array */
        if(merge_sort_merge(data, elem_size, start_idx, mid_idx, end_idx, compare) != 0)
            return -1;
    }

    return 0;
}




/*
*****************************
        Counting Sort
*****************************
*/

/* Perform Counting Sort */
int counting_sort(int *data, int num_elem, int max)
{
    /* Allocate memory for the array that will hold the counts of each element */
    int *counts = malloc(max * sizeof(int));
    if(counts == NULL)
        return -1;

    /* Allocate memory for the array that will contain the sorted elements */
    int *sorted = malloc(num_elem * sizeof(int));
    if(sorted == NULL)
    {
        free(counts);
        return -1;
    }

    /* Initialize the counts */
    for(int i = 0; i < max; i++)
        counts[i] = 0;
    
    /* Count the occurences of each element */
    for(int i = 0; i < num_elem; i++)
        counts[data[i]] += 1;
    
    /* Adjust each count to reflect the counts before it */
    for(int i = 1; i < max; i++)
        counts[i] += counts[i - 1];

    /* Use the counts to position each element in the sorted array */
    for(int i = num_elem - 1; i >= 0; i--)
    {
        int idx = counts[data[i]] - 1;
        sorted[idx] = data[i];
        counts[data[i]] -= 1;
    }
    
    /* Now, sorted contains the sorted elements, so copy it back into data */
    memcpy(data, sorted, num_elem * sizeof(int));

    /* Cleanup */
    free(counts);
    free(sorted);

    return 0;
}  




/*
**************************
        Radix Sort
**************************
*/

/* Perform Radix Sort */
int radix_sort(int *data, int num_elem, int num_pos, int radix)
{
    /* Allocate memory for the array that will hold the counts of each digit */
    int *counts = malloc(radix * sizeof(int));
    if(counts == NULL)
        return -1;

    /* Allocate memory for the array that will hold the sorted elements */
    int *sorted = malloc(num_elem * sizeof(int));
    if(sorted == NULL)
    {
        free(counts);
        return -1;
    }

    /* Sort from least-significant digit to most-significant digit */
    for(int d = 0; d < num_pos; d++)
    {
        /* Initialize the counts */
        for(int i = 0; i < radix; i++)
            counts[i] = 0;

        /* Calculate the value at the digit's position (e.g., The the digit 2 in 123 with radix 10 has value 2*(10^1) = 20) */
        int digit_val = (int)pow((double)radix, (double)d);

        /* Count the occurences of each digit value */
        for(int i = 0; i < num_elem; i++)
        {
            int idx = (data[i] / digit_val) % radix;
            counts[idx] += 1;
        }

        /* Ajust each count to reflect the counts before it */
        for(int i = 1; i < radix; i++)
            counts[i] += counts[i - 1];
        
        /* Use the counts to position each element where it belongs */
        for(int i = num_elem - 1; i >= 0; i--)
        {
            int idx = (data[i] / digit_val) % radix;
            sorted[counts[idx] - 1] = data[i];
            counts[idx] -= 1;
        }

        /* Now, sorted contains data sorted thus far, so copy it into data */
        memcpy(data, sorted, num_elem * sizeof(int));
    }

    /* Cleanup */
    free(counts);
    free(sorted);

    return 0;
} 
   

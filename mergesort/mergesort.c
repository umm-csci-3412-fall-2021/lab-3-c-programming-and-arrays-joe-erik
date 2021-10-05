#include "mergesort.h"


/**
 * Average two integers without overflowing.
 */
int safe_average(int a, int b) {
    // Source: https://www.geeksforgeeks.org/compute-average-two-numbers-without-overflow/
    return a / 2 + b / 2 + (a % 2 + b % 2) / 2;
}

/**
 * The "merge" step of the merge sort, where we join two sorted subarrays into
 * one big sorted subarray.
 *
 * This function joins the subarrays from `start`, inclusive, to `midpoint`,
 * exclusive, and from `midpoint`, inclusive, to `end`, exclusive.
 */
void mergeRanges(int start, int midpoint, int end, int values[]) {
    // Keep the sorted version of the range in a temporary array for the
    // moment.
    int sortedRange[end - start];

    // i is an index showing where we are in the sortedRange;
    // j is an index showing where we are in the first subarray;
    // k is an index showing where we are in the second subarray.
    int i = 0;
    int j = start;
    int k = midpoint;

    while (j < midpoint && k < end) {
        if (values[j] < values[k]) {
            sortedRange[i] = values[j];
            j++;
            i++;
        } else {
            sortedRange[i] = values[k];
            k++;
            i++;
        }
    }

    // At this point we've exhausted one of the subarrays, so just fill
    // sortedRange with the other subarray.
    // (Note that only one of these while loops will run, depending on which
    // subarray still has values in it.)

    while (j < midpoint) {
        sortedRange[i] = values[j];
        j++;
        i++;
    }

    while (k < end) {
        sortedRange[i] = values[k];
        k++;
        i++;
    }

    // Copy the data back to `values`.
    for (int m = 0; m < end - start; m++) {
        values[m + start] = sortedRange[m];
    }
}

/**
 * Sort a subrange of an array in place.
 *
 * This method sorts the indices of the array between `start`, inclusive, and
 * `end`, exclusive.
 */
void mergesortRange(int start, int end, int values[]) {
    if (end - start <= 1) {
        // There's one or fewer elements in the range, so it's already sorted.
        return;
    } else {
        int midpoint = safe_average(start, end);
        mergesortRange(start, midpoint, values);
        mergesortRange(midpoint, end, values);
        mergeRanges(start, midpoint, end, values);
    }
}

/**
 * Sort an array in place.
 *
 * `size` should be the length of the array.
 */
void mergesort(int size, int values[]) {
    mergesortRange(0, size, values);
}

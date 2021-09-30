#include "array_merge.h"
#include "../mergesort/mergesort.h"
#include <stdlib.h>

/**
 * Add up all the elements in an array
 *
 * `length` is the size of the array
 * `array_of_nums` is the array containing the elements to be added up
 */
int sum(int length, int* array_of_nums) {

    int sum = 0;

    for(int i = 0; i < length; i++) {
        sum += array_of_nums[i];
    }

    return sum;
}

/**
 * Takes a 2D array with varying lengths and flattens it into a single
 * 1D array.
 *
 * Note: the caller is in charge of freeing the returned value
 */
int* flatten_arrays(int num_arrays, int* sizes, int** values) {
    int totalLength = sum(num_arrays, sizes);

    int* combinedArray = (int*) calloc(totalLength, sizeof(int));

    // Counter to keep track of where we are in `combinedArray`
    int currentIndex = 0;

    for(int i = 0; i < num_arrays; i++) {

        for(int j = 0; j < sizes[i]; j++) {

            combinedArray[currentIndex] = values[i][j];
            currentIndex++;
        }
    }

    return combinedArray;
}


/**
 * Counts the number of Unique integers in a sorted array.
 */
int count_unique(int length, int* values) {

    if(length == 0) {
        return 0;
    }

    int numUnique = 1;
    int lastSeen = values[0];

    for(int i = 1; i < length; i++) {
        if(values[i] != lastSeen) {
            numUnique++;
            lastSeen = values[i];
        }
    }

    return numUnique;
}


/**
 * Given a sorted list of integers, return a new array with duplicate elements
 * removed.
 *
 * The first element of the returned array is the number of unique elements;
 * the rest of the array contains the unique elements in sorted order.
 */
int* remove_duplicates(int length, int* values) {

    int numUnique = count_unique(length, values);

    int* uniqueArray = (int*) calloc(numUnique + 1, sizeof(int));
    uniqueArray[0] = numUnique;

    if(length == 0) {
        return uniqueArray;
    }

    uniqueArray[1] = values[0];
    int lastSeen = values[0];

    // Keep track of where we are in uniqueArray
    int currentIndex = 2;

    for(int i = 1; i < length; i++) {
        if(values[i] != lastSeen) {
            uniqueArray[currentIndex] = values[i];
            lastSeen = values[i];
            currentIndex++;
        }
    }

    return uniqueArray;
}


int* array_merge(int num_arrays, int* sizes, int** values) {

    int* flatArray = flatten_arrays(num_arrays, sizes, values);
    int totalLength = sum(num_arrays, sizes);

    mergesort(totalLength, flatArray);

    int* finalArray = remove_duplicates(totalLength, flatArray);

    free(flatArray);

    return finalArray;
}

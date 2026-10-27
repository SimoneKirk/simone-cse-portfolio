
#include <stdio.h>
#include <stdlib.h>

void printArray(int**, int);

int main() {
    int i = 0, j = 0, n = 5;

    // Allocate space for 5 row pointers
    int **arr = (int**)malloc(n * sizeof(int*));
    // malloc reserves memory for n pointers.

    // (3) Allocate and initialize the 2-D array to 0
        // The outer loop goes through each of the 5 rows. Heap
    for(i = 0; i < n; i++) {
        *(arr + i) = (int*)malloc(n * sizeof(int));

        for(j = 0; j < n; j++) {
            *(*(arr + i) + j) = 0; //move to row i, derefrence to get adress of integers.
        }
    }

    // (4) Print the array filled with zeros
    printArray(arr, n);

    // (6) Make arr a diagonal matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j) {
                *(*(arr + i) + j) = i + 1;
            }
        }
    }

    // (7) Print the diagonal matrix
    printArray(arr, n);

    // Free the memory for each row
    for(i = 0; i < n; i++) {
        free(*(arr + i));
    }

    // Free the row pointers
    free(arr);

    return 0;
}

void printArray(int **array, int size) {
    // (5) Print the 2-D array
    int i, j;

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            printf("%d ", *(*(array + i) + j));
        }
        printf("\n");
    }
}

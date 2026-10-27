
#include <stdio.h>
#include <stdlib.h>

int** matMult(int **a, int **b, int size) {
	// (4) Implement your matrix multiplication here. 
	// You will need to create a new matrix to store the product.
    int i, j, k; //row, column, across A down B
    int **result; //point to new Matrix C

//Allocate the row pointers - 5 places
    result = (int**)malloc(size * sizeof(int*));
//amount of bytes to store int pointer

//The loop runs with i = 0, 1, 2, 3, 4. -allocates space for five integers in one row.
    for(i = 0; i < size; i++) {
        *(result + i) = (int*)malloc(size * sizeof(int));
//Visit every element
        for(j = 0; j < size; j++) {
            *(*(result + i) + j) = 0; //sets the current result element to zero
//“the element at row i, column j,” equivalent to result[i][j].

//Calculate the product
            for(k = 0; k < size; k++) {
                *(*(result + i) + j) +=
                    (*(*(a + i) + k)) * (*(*(b + k) + j));
            }
        }
    }

    return result;
}

void printArray(int **arr, int n) {
	// (2) Implement your printArray function here
    int i, j;

    for(i = 0; i < n; i++) { ////outer loop selects a row.
        for(j = 0; j < n; j++) { //inner loop prints each value in that row.
            printf("%d ", *(*(arr + i) + j)); //move to row i, derefrence to get adress of integers.
        }
        printf("\n"); //next line after row is printed.
    }
}

int main() {
	int i, j, n = 5; //changed int n=0
	int **matA, **matB, **matC;
	// (1) Define 2 (n x n) arrays (matrices).
	n = 5;

//allocates space for five row pointers for each matrix
matA = (int**)malloc(n * sizeof(int*));
matB = (int**)malloc(n * sizeof(int*));

//loop allocates five integers for each row of A and B
for(i = 0; i < n; i++) {
    *(matA + i) = (int*)malloc(n * sizeof(int));
    *(matB + i) = (int*)malloc(n * sizeof(int));

//Initialize the matrix values
    for(j = 0; j < n; j++) {
        *(*(matA + i) + j) = i + 1; //every value in a row of A is the same.
        *(*(matB + i) + j) = j + 1; //every row of B contains 1, 2, 3, 4, 5.
    }
} 
//Print matrices A and B
	// (3) Call printArray to print out the 2 arrays here.
	printf("Matrix A:\n");
	printArray(matA, n);

	printf("Matrix B:\n");
	printArray(matB, n);

//matMult() with A, B, and the size 5
	// (5) Call matMult to multiply the 2 arrays here.
	matC = matMult(matA, matB, n);

//prints the completed product matrix.	
	// (6) Call printArray to print out resulting array here.
	printf("Matrix C:\n");
	printArray(matC, n);	

    return 0;
}
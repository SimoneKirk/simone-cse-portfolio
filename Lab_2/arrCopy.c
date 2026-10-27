#include <stdio.h>      // Gives us printf() and scanf()
#include <string.h>     // Gives us string functions
#include <stdlib.h>     // Gives us malloc()

int size; // Global variable that stores the size of the original array.
int evenCount = 0; // Counts how many even numbers are in the array.
int oddCount = 0; 
int *arr; // Pointer that will point to the original array.
int *arr_even; // Pointer that will point to the new array containing even numbers.
int *arr_odd;

char *str1 = "Original array's contents: "; // Message that will be printed before the original array.
char *str2 = "Contents of new array containing even elements from original: ";
char *str3 = "Contents of new array containing odd elements from original: ";// Message that will be printed before the odd array.


/*
 * This function prints the contents of an integer array.
 *
 * a = pointer to the array
 * size = number of elements in the array
 * prompt = message to print before the array
 */
void printArr(int *a, int size, char *prompt){

    printf("%s", prompt);  // Print the message passed into the function.

    if (size == 0) {  //Check if the array has no elements.

        printf("empty\n"); // Print "empty" if the array has no elements.

        return;
    }

    for (int i = 0; i < size; i++) { // Loop through every element in the array.

        printf("%d ", *(a + i)); // *(a + i) accesses the value at position i.
    }

    printf("\n");
}

/*
 * This function copies the even numbers into arr_even
 * and the odd numbers into arr_odd.
 */
void arrCopy(){

    
    int evenIdx = 0; // Keeps track of the next position in the even array.

    int oddIdx = 0;

    for (int i = 0; i < size; i++) { // Loop through every element of the original array.

        // % gives the remainder.
        if (*(arr + i) % 2 == 0) { // Check if the current number is even.

            // Copy the even number into arr_even.
            // evenIdx tells us where to put it.
            *(arr_even + evenIdx) = *(arr + i);

            // Move to the next position in the even array.
            evenIdx++;

        } else {

            // The number is odd, so copy it into arr_odd.
            *(arr_odd + oddIdx) = *(arr + i);

            // Move to the next position in the odd array.
            oddIdx++;
        }
    }
}

/*
 * main() is where the program starts.
 */
int main(){

    int i;   // Create an integer variable used for the input loop.

    printf("Enter the size of array you wish to create: ");  // Ask the user how many numbers they want in the array.


    scanf("%d", &size);  // Read the user's size and store it in size. &size gives scanf() the address of size.

    // size * sizeof(int) calculates how many bytes are needed.
    // malloc() gives us memory from the heap.
    // arr stores the address of that memory.
    arr = (int*) malloc(size * sizeof(int)); // Allocate enough memory for the original array. Dynamic allocation, multiply by 4.


    // Loop through every position in the original array.
    for (i = 0; i < size; i++) {

        printf("Enter array element #%d: ", i + 1); // i + 1 makes the displayed number start at 1 instead of 0.

        scanf("%d", arr + i); //Read the number from the user. arr + i points to the current position in the array


        // Check whether the number is even.
        if (*(arr + i) % 2 == 0) {

            // Increase the number of even elements by 1.
            evenCount++;

        } else {

            // Otherwise, the number is odd.
            oddCount++;
        }
    }

    // evenCount tells us exactly how many even numbers
    // the new array needs to hold.
    arr_even = (int*) malloc(evenCount * sizeof(int));     // Allocate enough memory for the even array.


    arr_odd = (int*) malloc(oddCount * sizeof(int)); // Allocate enough memory for the odd array.


/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/

    // Print the original array.
    printArr(arr, size, str1);


    // Separate the original array into
    // the even and odd arrays.
    arrCopy();

    printArr(arr_even, evenCount, str2);

    printArr(arr_odd, oddCount, str3);

    printf("\n");

    return 0;
}
#include <stdio.h>   // Provides printf(), scanf(), and file input/output functions
#include <stdlib.h>  // Provides malloc() and free()
#include <string.h>  // Provides strcat()

// Stores the number of rows and columns in the square puzzle
int bSize;

// Function declarations
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);

// Compares two letters without considering uppercase or lowercase
int sameLetterIgnoreCase(char a, char b) {
    // Convert the first letter to lowercase if it is uppercase
    if (a >= 'A' && a <= 'Z') a = (char)(a - 'A' + 'a');

    // Convert the second letter to lowercase if it is uppercase
    if (b >= 'A' && b <= 'Z') b = (char)(b - 'A' + 'a');

    // Return 1 if the letters match, or 0 if they do not
    return a == b;
}

// Counts the number of characters in a string
int wordLen(const char* s) {
    int n = 0;

    // Move through the string until reaching its null terminator
    while (*(s + n) != '\0') n++;

    return n;
}

// Checks whether a row and column are inside the puzzle
int inBounds(int r, int c) {
    // Return 1 if both coordinates are valid; otherwise, return 0
    return (r >= 0 && r < bSize && c >= 0 && c < bSize);
}

// Converts an integer into a string without using sprintf()
void intToStr(int n, char* buf) {
    char* p = buf;
    int isNegative = 0;

    // Handle zero separately because the loop below requires n > 0
    if (n == 0) {
        *p = '0';
        *(p + 1) = '\0';
        return;
    }

    // Remember whether the number is negative
    if (n < 0) {
        isNegative = 1;
        n = -n;
    }

    // Extract each digit, starting with the rightmost digit
    while (n > 0) {
        *p = (n % 10) + '0';
        p++;
        n /= 10;
    }

    // Add the minus sign if the original number was negative
    if (isNegative) {
        *p = '-';
        p++;
    }

    // Mark the end of the string
    *p = '\0';

    // Reverse the characters because the digits were stored backward
    char* start = buf;
    char* end = p - 1;

    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }
}

// Adds a step number to the string for a particular puzzle cell
void appendStep(char* cellStr, int step) {
    // Allocate temporary space to store the step number as text
    char* tmp = (char*)malloc(16 * sizeof(char));

    // Stop if memory allocation fails
    if (tmp == NULL) return;

    // Convert the number to text and add it to the cell's string
    intToStr(step, tmp);
    strcat(cellStr, tmp);

    // Release the temporary memory
    free(tmp);
}

// Frees all memory used by the search-path grid
void freePath(char*** grid) {
    int r, c;

    // There is nothing to free if the grid pointer is NULL
    if (grid == NULL) return;

    // Visit every row in the path grid
    for (r = 0; r < bSize; r++) {
        char** i = *(grid + r);

        // Skip rows that were not successfully allocated
        if (i == NULL) continue;

        // Free each cell's character string
        for (c = 0; c < bSize; c++) {
            free(*(i + c));
        }

        // Free the row of cell pointers
        free(i);
    }

    // Free the main grid of row pointers
    free(grid);
}

// Creates an empty grid for storing the search path
char*** makeEmptyPath(void) {
    int r, c;

    // Allocate memory for the rows of the path grid
    char*** grid = (char***)malloc(bSize * sizeof(char**));

    if (grid == NULL) return NULL;

    // Allocate each row
    for (r = 0; r < bSize; r++) {
        *(grid + r) = (char**)malloc(bSize * sizeof(char*));

        // Clean up if row allocation fails
        if (*(grid + r) == NULL) {
            freePath(grid);
            return NULL;
        }

        // Allocate a string for every cell
        for (c = 0; c < bSize; c++) {
            *(*(grid + r) + c) = (char*)malloc(64 * sizeof(char));

            // Clean up if cell allocation fails
            if (*(*(grid + r) + c) == NULL) {
                freePath(grid);
                return NULL;
            }

            // Start each cell with an empty string
            *(*(*(grid + r) + c)) = '\0';
        }
    }

    return grid;
}

// Prints the numbered search path
void printPath(char*** pathGrid) {
    int r, c;

    // Visit each cell in the path grid
    for (r = 0; r < bSize; r++) {
        for (c = 0; c < bSize; c++) {
            char* s = *(*(pathGrid + r) + c);
            int Len;
            int pad;

            // Print the step number if this cell is part of the path
            if (s != NULL && *s != '\0') {
                printf("%s", s);

                // Add spaces between columns to align the output
                if (c != bSize - 1) {
                    Len = wordLen(s);
                    pad = 8 - Len;

                    // Always print at least one separating space
                    if (pad < 1) pad = 1;

                    while (pad > 0) {
                        printf(" ");
                        pad--;
                    }
                }
            } else {
                // A zero means this cell is not part of the search path
                printf("0");

                // Keep the columns aligned
                if (c != bSize - 1) {
                    pad = 7;

                    while (pad > 0) {
                        printf(" ");
                        pad--;
                    }
                }
            }
        }

        // Move to the next row
        printf("\n");
    }
}

// Recursively searches for the next letter in the word
int dfsFind(char** arr, const char* word, int wLen, int index,
            int r, int c, int* pathR, int* pathC) {
    int dr, dc;

    // Stop if the current position is outside the puzzle
    if (!inBounds(r, c)) return 0;

    // Stop if the current cell does not match the required letter
    if (!sameLetterIgnoreCase(*(*(arr + r) + c), *(word + index))) {
        return 0;
    }

    // Save the coordinates of the matching letter
    *(pathR + index) = r;
    *(pathC + index) = c;

    // The entire word has been matched
    if (index == wLen - 1) return 1;

    // Try all neighboring cells, including diagonals
    for (dr = -1; dr <= 1; dr++) {
        for (dc = -1; dc <= 1; dc++) {

            // Do not search the current cell again as its own neighbor
            if (dr == 0 && dc == 0) continue;

            // Recursively search for the next letter
            if (dfsFind(arr, word, wLen, index + 1,
                        r + dr, c + dc, pathR, pathC)) {
                return 1;
            }
        }
    }

    // No matching path was found from this position
    return 0;
}

// Main function: opens the puzzle file and starts the program
int main(int argc, char **argv) {
    // Require exactly one command-line argument: the puzzle filename
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }

    int i, j;
    FILE *fptr;

    // Open the puzzle file for reading
    fptr = fopen(argv[1], "r");

    // Stop if the file cannot be opened
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the square puzzle
    fscanf(fptr, "%d\n", &bSize);

    // Allocate memory for the puzzle rows and search word
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Check whether the initial memory allocations succeeded
    if (block == NULL || word == NULL) {
        free(block);
        free(word);
        fclose(fptr);
        return 1;
    }

    // Read the puzzle one row at a time
    for (i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));

        // Clean up and exit if a row cannot be allocated
        if (*(block + i) == NULL) {
            while (i > 0) {
                i--;
                free(*(block + i));
            }

            free(block);
            free(word);
            fclose(fptr);
            return 1;
        }

        // Read each character in the current row
        for (j = 0; j < bSize - 1; j++) {
            fscanf(fptr, "%c ", *(block + i) + j);
        }

        // Read the last character in the row
        fscanf(fptr, "%c \n", *(block + i) + j);
    }

    // The puzzle has been read, so the file can be closed
    fclose(fptr);

    // Ask the user which word to search for
    printf("Enter the word to search: ");
    scanf("%19s", word);

    // Display the original puzzle before searching
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    printf("\n");

    // Search for the requested word
    searchPuzzle(block, word);

    // Free the puzzle's allocated memory
    for (i = 0; i < bSize; i++) {
        free(*(block + i));
    }

    free(block);
    free(word);

    return 0;
}

// Prints the original puzzle in a readable grid
void printPuzzle(char** arr) {
    int i, j;

    // Print each row of the puzzle
    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {

            // Print the last character without an extra space
            if (j == bSize - 1) {
                printf("%c", *(*(arr + i) + j));
            } else {
                // Separate the puzzle characters with spaces
                printf("%c ", *(*(arr + i) + j));
            }
        }

        printf("\n");
    }
}

// Searches the puzzle for the requested word and prints its path
void searchPuzzle(char** arr, char* word) {
    int r, c;

    // Calculate the number of letters in the target word
    int wLen = wordLen(word);

    // Arrays that store the row and column of each matching letter
    int* pathR;
    int* pathC;

    // Grid that stores the step number for every cell in the path
    char*** pathGrid;

    // Tracks whether a matching path has been found
    int wordFound = 0;

    // Handle an empty search word
    if (wLen <= 0) {
        printf("Word not found!\n");
        return;
    }

    // Allocate space to remember the coordinates of each letter
    pathR = (int*)malloc(wLen * sizeof(int));
    pathC = (int*)malloc(wLen * sizeof(int));

    // Stop if either coordinate array cannot be allocated
    if (pathR == NULL || pathC == NULL) {
        free(pathR);
        free(pathC);
        printf("Word not found!\n");
        return;
    }

    // Create an initially empty grid for displaying the search path
    pathGrid = makeEmptyPath();

    // Stop if the path grid cannot be created
    if (pathGrid == NULL) {
        printf("Word not found!\n");
        free(pathR);
        free(pathC);
        return;
    }

    // Try every cell as a possible starting point
    for (r = 0; r < bSize; r++) {
        for (c = 0; c < bSize; c++) {

            // Skip cells that do not match the first letter
            if (!sameLetterIgnoreCase(*(*(arr + r) + c), *word)) {
                continue;
            }

            // Search recursively for the remaining letters
            if (dfsFind(arr, word, wLen, 0, r, c, pathR, pathC)) {
                int k;

                // Record the step number for each letter in the found path
                for (k = 0; k < wLen; k++) {
                    int pr = *(pathR + k);
                    int pc = *(pathC + k);

                    // Store steps as text in their corresponding cells
                    appendStep(*(*(pathGrid + pr) + pc), k + 1);
                }

                // Stop searching after finding the first matching path
                wordFound = 1;
                break;
            }
        }

        // Leave the outer loop once a path has been found
        if (wordFound) break;
    }

    // Display the result
    if (wordFound) {
        printf("Word found!\n");
        printf("Printing the search path:\n");
        printPath(pathGrid);
    } else {
        printf("Word not found!\n");
    }

    // Release all memory used for the search
    freePath(pathGrid);
    free(pathR);
    free(pathC);
}
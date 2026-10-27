#include <stdio.h>      // Gives us printf() and scanf()
#include <string.h>     // Gives us strlen() for finding string length

/*
 * This function adds the characters from s2
 * to the end of s1.
 *
 * We assume s1 has enough space to hold
 * the combined string.
 */

/*
 * char* means the function returns a pointer to a character.
 * append is the name of the function.
 * s1[] is the first string.
 * s2[] is the second string.
 */
char* append(char s1[], char s2[]) {

    int s1len = strlen(s1);  // Find how many characters are in s1. Example: "HI!" has a length of 3.

    int s2len = strlen(s2); // Find how many characters are in s2. Example: "hi!" has a length of 3.

    
    int k; // Create a variable called k. We use k to keep track of the loop.

    for (k = 0; k < s2len; k++) { // Repeat the loop once for every character in s2. 
    //k starts at 0 and stops before s2len.

        // Copy one character from s2 into s1.
        // s1len tells u where the end of the original s1 is.
        // k moves through each character of s2.
        //
        // Example:
        // s1 = "HI!"
        // s2 = "hi!"
        //
        // s1[3] = 'h'
        // s1[4] = 'i'
        // s1[5] = '!'
        s1[k + s1len] = s2[k];
    }

    // Add '\0' to mark the end of the new string.
    // This tells C where the string stops.
    s1[s1len + s2len] = '\0';

    return s1;
}


/*
 * main() is where the program starts running.
 */
int main() {

    char str1[10];
    // Create a character array that can hold up to 9 characters
    // plus the '\0' at the end.

    char str2[10];  // Create another character array for the second string.

    while (1) { // while(1) creates an infinite loop. Keeps printing until Ctrl C.
 
        printf("str1 = ");  // Display "str1 = " on the screen.

        // Read the first string from the user.
        // %[^\n] allows the user to enter spaces.
        // %*c removes the Enter/newline character.
        scanf("%[^\n]%*c", str1);

        // This is an alternative way to read the string.
        // It is commented out, so it does NOT run.
        // if (!gets(str1)) return 0;


        printf("str2 = ");  // Display "str2 = " on the screen.

        // Read the second string from the user.
        // %[^\n] allows spaces.
        // %*c removes the Enter/newline character.
        scanf("%[^\n]%*c", str2);

        // Alternative input method.
        // It is commented out, so it does NOT run.
        // if (!gets(str2)) return 0;


        // Call append() to add str2 to the end of str1.
        // The returned combined string is printed with %s.
        printf("The result of appending str2 to str1 is %s.\n",
               append(str1, str2));

        // Flush the input stream - clean.
        fflush(stdin);
    }

    return 0;
}
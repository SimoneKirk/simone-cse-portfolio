#include <stdio.h> 

/*
 * This function reads numbers entered by the user.
 * It adds the numbers together and stores the sum.
 * It returns how many numbers the user entered.
 */


/*
 * We cannot use global variables.
 *
 * The parameter must be changed so that the function
 * can update the original sum variable in main().
 */
int read_values(double *sum) {

    int values = 0, input = 0; // values counts how many numbers the user enters.

    *sum = 0; // Set the sum to 0 before starting.

    printf("Enter input values (enter 0 to finish):\n"); // Tell the user how to enter the numbers.

    // Read the first number.
    // &input gives scanf() the address of input.
    scanf("%d", &input);

    // Keep looping while the user has not entered 0.
    while(input != 0) {

        // Increase the number of values by 1.
        values++;

        *sum += input; // Add the current input to the sum.

        // &input is required because scanf() needs
        // the address where it should store the number.
        scanf("%d", &input); //add & to get adress of input.
    }

    // Return the number of values entered.
    return values;
}


int main() {

    // Create a double variable to store the sum.
    double sum = 0;

    // Create an integer to store how many values were entered.
    int values;

    values = read_values(&sum);    // &sum sends the ADDRESS of sum to the function. 
    // This allows read_values() to change the original sum.
   
    // %g prints the answer as a number.
    printf("\nAverage: %g\n", sum / values);  // Calculate and print the average.

    return 0;
}
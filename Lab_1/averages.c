#include <stdio.h>

int main() {

int evenSum = 0; //Adds numbers whose digit sum is even
int oddSum = 0;
int evenCount = 0; //Counts numbers in the even group
int oddCount = 0;
int inputCounter = 1;
int number;
int digitSum;
int temp;
int digit;
double evenAverage;
double oddAverage;

number = -1;
//while loop
while (number != 0) {

if (inputCounter == 1) {
    printf("Enter the 1st value: ");
}
else if (inputCounter == 2) {
    printf("Enter the 2nd value: ");
}
else if (inputCounter == 3) {
    printf("Enter the 3rd value: ");
}
else if (inputCounter % 10 == 1 && inputCounter % 100 != 11) {
    printf("Enter the %dst value: ", inputCounter);
}
//modulo (remainder)
else if (inputCounter % 10 == 2 && inputCounter % 100 != 12) {
    printf("Enter the %dnd value: ", inputCounter);
}
else if (inputCounter % 10 == 3 && inputCounter % 100 != 13) {
    printf("Enter the %drd value: ", inputCounter);
}
else {
    printf("Enter the %dth value: ", inputCounter);
}
    scanf("%d", &number);
//stop loop
if (number == 0) { //Zero is the sentinel value
   break; 
}

digitSum = 0; //like initializing, so it has a clean start
temp = number; //So I can manipulate the digits without changing the original number.

if (temp < 0) {
    temp = -temp;
}

while (temp > 0) {

    digit = temp % 10; //It gets the last digit.
    digitSum = digitSum + digit; // 23 2+3=6 23 = even
    temp = temp / 10;

}
//remainder 0, even number
if (digitSum % 2 == 0) {

    evenSum = evenSum + number; 
    evenCount = evenCount + 1;

}
else {

oddSum = oddSum + number;
oddCount = oddCount + 1;

}

inputCounter++;

}


if (evenCount > 0) {

    evenAverage = (double) evenSum / evenCount;
    printf("Average of input values whose digits sum up to an even number: %.2f\n", evenAverage);

}

if (oddCount > 0) {

    oddAverage = (double) oddSum / oddCount;
    printf("Average of inputs whose digits sum up to an odd number: %.2f\n", oddAverage);

}

if (evenCount == 0 && oddCount == 0) {
    printf("There is no average to compute.\n");
}
    return 0;
}
//This program repeatedly asks the user for integer 
//values until they enter 0. For each number, it adds up the digits. 
//If the digit sum is even, the number goes into the even group. 
//If the digit sum is odd, it goes into the odd group. 
//At the end, the program calculates the average for each group.
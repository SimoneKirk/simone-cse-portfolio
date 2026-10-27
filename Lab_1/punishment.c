#include <stdio.h>

int main() {
    int repetitionCount;
    int typoPlacement;
    int i;

    printf("Enter the repetition count for the punishment phrase: ");
    scanf("%d", &repetitionCount);

    while (repetitionCount <= 0) {
        printf("You entered an invalid value for the repetition count! Please re-enter: ");
        scanf("%d", &repetitionCount);
    }

    printf("Enter the line where you want to insert the typo: ");
    scanf("%d", &typoPlacement);
    //typo less than or equal to 0 invalid
//typo greater than count then invalid
    while (typoPlacement < 1 || typoPlacement > repetitionCount) {
        printf("You entered an invalid value for the typo placement! Please re-enter: ");
        scanf("%d", &typoPlacement);
    }

    for (i = 1; i <= repetitionCount; i++) {
        if (i == typoPlacement) {
            printf("Cading wiht is C avesone!\n");
        } else {
            printf("Coding with C is awesome!\n");
        }
    }

    return 0;
}
#include <stdio.h>

int main() {

    int x = 2;
    int y = 3;
    int *px;
    int *py;

    int arr[10] = {4};

    printf("x value: %d\n", x);
    printf("y value: %d\n", y);
    printf("first array value: %d\n", arr[0]);

    printf("x address: %p\n", (void *)&x);
    printf("y address: %p\n", (void *)&y);

    px = &x;
    py = &y;

    printf("px points to: %p\n", (void *)px);
    printf("py points to: %p\n", (void *)py);

    int i;

    for (i = 0; i < 10; i++) {
        printf("arr[%d] = %d\n", i, *(arr + i));
    }

    printf("arr address: %p\n", (void *)arr);
    printf("arr[0] address: %p\n", (void *)&arr[0]);
    printf("whole array address: %p\n", (void *)&arr);

    return 0;
}
/*
Write a program that reads a number form the standard input,
than prints "Odd" if the number is odd, or "Even" it it is even.
*/

#include <stdio.h>

int main() {

    int number;

    printf("Give me an integer: ");
    scanf("%d", &number);
    if (number%2 != 0) {
        printf("The number is odd.\n");
    } else {
        printf("The number is even.\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdint.h>

int main() {
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer = &numbers[0];
    //TODO:
    // The "number_pointer" should point to the third element of the array called "numbers",
    // then please print its value with it. Solve the problem without reusing the "&" operator
    // for getting the address of the third element.
    number_pointer = numbers + 2;
    printf("The third element is %d\n", *number_pointer);

    return 0;
}

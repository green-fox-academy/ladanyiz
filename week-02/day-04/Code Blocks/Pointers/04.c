#include <stdio.h>
#include <stdint.h>

int main() {
    int numbers[] = {5, 6, 7, 8, 9};
    int* pNumbers;
    //TODO:
    // The "number_pointer" should point to the first element of the array called "numbers",
    // than please print its value with it.
    pNumbers = numbers; // = &numbers[0]
    printf("The first element is %d\n", *pNumbers);

    return 0;
}

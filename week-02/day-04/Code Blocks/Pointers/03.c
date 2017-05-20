#include <stdio.h>
#include <stdint.h>

int main() {
    int number = 1234;
    int* pNumber = &number;
    //TODO:
    // update the value of number variable to 42 using the "number_pointer"
    *pNumber = 42;
    printf("The new number is %d\n", *pNumber);

    return 0;
}

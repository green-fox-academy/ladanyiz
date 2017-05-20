#include <stdio.h>
#include <stdint.h>

int main() {
    int number = 1234;
    //TODO:
    // print the memory address of the variable
    int* pNumber = &number;
    printf("The memory address of the 'number' variable is %d", pNumber);

    return 0;
}

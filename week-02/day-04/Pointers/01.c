#include <stdio.h>
#include <stdint.h>

int main() {
    int number = 1234;
    //TODO:
    // print the memory address of the variable
    int *ptr_number = &number;
    printf("The memory address of the 'number' variable is %d", ptr_number);

    return 0;
}

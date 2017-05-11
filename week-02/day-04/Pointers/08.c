#include <stdio.h>
#include <stdint.h>

int main() {
    int high_number = 6655;
    int low_number = 2;

    int* high_number_pointer = &low_number;
    int* low_number_pointer = &high_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.
    int* temp_ptr;
    temp_ptr = high_number_pointer;
    high_number_pointer = low_number_pointer;
    low_number_pointer = temp_ptr;
    printf("The high number is %d\n", *high_number_pointer);
    printf("The low number is %d\n", *low_number_pointer);

    return 0;
}

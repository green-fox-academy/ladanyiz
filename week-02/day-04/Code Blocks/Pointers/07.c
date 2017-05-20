#include <stdio.h>
#include <stdint.h>

int main() {
    int high_number = 6655;
    int low_number = 2;

    int* pHigh_number = &low_number;
    int* pLow_number = &high_number;
    //TODO:
    // Please fix the problem and swap where the pointers point,
    // without using the "&" operator.
    int* temp_ptr;
    temp_ptr = pHigh_number;
    pHigh_number = pLow_number;
    pLow_number = temp_ptr;
    printf("The high number is %d\n", *pHigh_number);
    printf("The low number is %d\n", *pLow_number);

    return 0;
}

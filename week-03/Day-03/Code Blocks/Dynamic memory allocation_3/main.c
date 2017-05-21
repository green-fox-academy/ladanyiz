
//NOT OK!!!

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** TODO:
 * Create a function called "range" that creates a new array and returns a pointer to it.
 * It should fill the array with numbers based on it's paramters.
 * It should take 3 paramters:
 * int from: the first number in the array
 * int to: it will fill the array till it would reach this number (so this number is not in the array)
 * int step: the step between the numbers
 *
 * Examples:
 * range(0, 10, 2) -> {0, 2, 4, 6, 8}
 * range(1, -8, -3) -> {1, -2, -5}
 *
 * It should delete any dynamically allocated resource before the program exits.
 */

uint8_t i;

int* range(int from, int to, int step) {

    int size = (to - from) / step;
    if (((to - from) % step) != 0) {
        size++;
    }

    // test
    printf("%d\n", size);

    int* ptr = calloc(size, sizeof(int));

    // test
    printf("%d\n", sizeof(ptr));

    for (i = 0; i < size; i++) {
        ptr[i] = from + step*i;
    }

    return ptr;
}

int main() {

    int* array1 = range(0, 20, 4);

    // test
    printf("%d\n", sizeof(array1));

    for (i = 0; i < sizeof(array1); i++) {
        printf("%d\t", array1[i]);
    }
    printf("\n");
/*
    int* array2 = range(1, -8, 3);

    for (i = 0; i < sizeof(array2); i++) {
        printf("%d\t", array2[i]);
    }
    printf("\n");
*/
    free(array1);
    //free(array2);

    return 0;
}

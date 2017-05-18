
//NOT READY!!!

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */

int* resize(int* array, int current_size, int new_size) {
    int* ptr = realloc(array, new_size);
    if (new_size > current_size) {
        for (int i = current_size; i < new_size; i++) {
            ptr[i] = 0;
        }
    }
    return ptr;
}

int main() {

    int* numbers = calloc(10, sizeof(int));
    numbers = {1, 2, 3, 4, 5, 6, 7, 8 ,9, 10};
    int* new = resize(numbers, 10, 15);
    for (int i = 0, i < 15; i++) {
        printf("%d\t", new[i]);
    }
    printf("\n");

    return 0;
}

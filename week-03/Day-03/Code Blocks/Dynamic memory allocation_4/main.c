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

uint8_t i;

int* resize(int* array, int current_size, int new_size) {

    int* new_array = calloc(new_size, sizeof(*new_array));

    if (new_size < current_size) {
        printf("New size is smaller than original!\n");
        return NULL;
    } else {
        for (i = 0; i < current_size; i++) {
            new_array[i] = array[i];
        }
    }
    if (new_size > current_size) {
        for (i = current_size; i < new_size; i++) {
            new_array[i] = 0;
        }
    }

    free(array);

    return new_array;
}

int main() {

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8 ,9, 10};

    int* new = resize(numbers, 10, 9);

    for (i = 0; i < 15; i++) {
        printf("%d\t", new[i]);
    }
    printf("\n");

    free(new);

    return 0;
}

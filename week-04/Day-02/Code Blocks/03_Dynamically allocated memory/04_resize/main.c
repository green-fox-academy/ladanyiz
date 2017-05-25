#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */

int *resize(int *array, int current_size, int new_size)
{
    int *new_array = calloc(new_size, sizeof(int));
    int i;

    for (i = 0; i < current_size; i++)
        new_array[i] = array[i];

    if (new_size > current_size) {
        for (int j = i; j < new_size; j++) {
            new_array[j] = 0;
        }
    }

    free(array);

    return new_array;
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};

    int *new_array = resize(array, 8, 14); // so that the dynamically allocated memory can be freed

    for (int i = 0; i < 14; i++)
        printf("%d\t", new_array[i]);

    free(new_array);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* pointer = NULL;

    // TODO:
    // Please allocate a 5 long array and fill it with numbers from 0 to 4, then print the whole array
    // Please delete the array before the program exits
    int *array = calloc(5, sizeof(int));

    for (int i = 0; i < 5; i++) {
        array[i] = i;
        printf("%d\n", array[i]);
    }

    free(array);

    return 0;
}
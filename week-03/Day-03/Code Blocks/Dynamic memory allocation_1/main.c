#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int* pointer = NULL;
    uint8_t i;
    // TODO:
    // Please allocate a 5 long array and fill it with numbers from 0 to 4, then print the whole array
    // Please delete the array before the program exits
    pointer = calloc(5, sizeof(int));

    for (i = 0; i < 5; i++) {
        pointer[i] = i;
    }

    for (i = 0; i < 5; i++) {
        printf("%d\t", pointer[i]);
    }

    free(pointer);
    printf("\n");
    return 0;
}

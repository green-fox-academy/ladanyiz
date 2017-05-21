#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it should print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main() {

    uint8_t count;
    float number;
    float sum = 0;

    printf("How many numbers will you enter? ");
    scanf("%d", &count);

    float* array = calloc(count, sizeof(float));

    for (uint8_t i = 0; i < count; i++) {
        printf("%d. number: ", i + 1);
        scanf("%f", &array[i]);
        sum += array[i];
    }

    printf("The average of these numbers is %.2f\n", sum / count);

    free(array);

    return 0;
}

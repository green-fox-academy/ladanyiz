#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it should print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main()
{
    int count;

    printf("How many numbers will you enter? ");
    scanf("%d", &count);

    int *numbers = calloc(count, sizeof(int));
    int sum = 0;

    for (int i = 0; i < count; i++) {
        printf("%d. number: ", i + 1);
        scanf("%d", &numbers[i]);
        sum += numbers[i];
    }

    float avg = (float) sum / count;

    printf("Their average is %.2f\n", avg);

    free(numbers);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
Create a program which writes down the following sentence 100 times:
"I won't cheat on the test!"

Do it with:
    - for loop
    - while loop
    - do while loop

Also create a funtion which does the same.
*/

uint8_t i;

void punishment() {

    for (i = 0; i < 100; i++) {
        printf("%d. I won't cheat on the test!\n", i + 1);
    }

    printf("\n");

    i = 0;
    while (i < 100) {
        printf("%d. I won't cheat on the test!\n", i + 1);
        i++;
    }

    printf("\n");

    i = 0;
    do {
        printf("%d. I won't cheat on the test!\n", i + 1);
        i++;
    } while (i < 100);
}

int main() {

    for (i = 0; i < 100; i++) {
        printf("%d. I won't cheat on the test!\n", i + 1);
    }

    printf("\n");

    i = 0;
    while (i < 100) {
        printf("%d. I won't cheat on the test!\n", i + 1);
        i++;
    }

    printf("\n");

    i = 0;
    do {
        printf("%d. I won't cheat on the test!\n", i + 1);
        i++;
    } while (i < 100);

    printf("\n");

    punishment();

    return 0;
}

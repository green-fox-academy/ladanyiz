#include <stdio.h>
#include <stdint.h>

int main() {
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";

	//TODO:
    // Print out the two arrays character-by-character
    for (uint8_t i = 0; i < 4; i++) {
        printf("%c\t", char_array[i] );
    }

    printf("\n");

    for (uint8_t i = 0; i < strlen(char_array_the_same); i++) {
        printf("%c\t", char_array_the_same[i] );
    }

	//TODO:
    // What is the difference between the arrays?
    // There is no '\0' ending character at the end of the first.

    return 0;
}

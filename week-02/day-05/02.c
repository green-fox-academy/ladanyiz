#include <stdio.h>
#include <stdint.h>
#include <string.h>

char* create_palindrome(char word[60]) {

    uint8_t len = strlen(word);
    char temp[len];

    for (int8_t i = len-1; i > -1; i--){
        temp[len -1 -i] = word[i];
    }
    strcat(word, temp);
    return word;
}

int main() {

    char input[30];

    while (1) {
        printf("Give me a word: ");
        gets(input);
        printf("Its palindrome is %s\n", create_palindrome(input));
    }

    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void capital(char input[]){
    for (uint8_t i = 0; i < strlen(input); i++)
        input[i] = toupper(input[i]);
}

void arrange(char input[]){
    uint8_t tmp;
    for (uint8_t i = strlen(input)-1; i > 0; i--)
        for (uint8_t j = 0; j < i; j++)
            if(input[j] > input[j+1]){
                tmp = input[j];
                input[j] = input[j+1];
                input[j+1] = tmp;
            }
}

int is_anagram(char one[], char two[]){

    capital(one);
    arrange(one);

    capital(two);
    arrange(two);

    uint8_t anagram = 1;

    if ((strcmp(one, two)) != 0)
        anagram = 0;

    return anagram;
}

int main() {

    char first[20];
    char second[20];

    printf("Are they anagrams?\n");
    printf("First word: ");
    gets(first);
    printf("Second word: ");
    gets(second);
    if (strlen(first) != strlen(second)){
        printf("They are not the same length, so obviously not!\n");
    }
    else if (is_anagram(first, second) == 1){
        printf("Yes, they are!\n");
    }
    else {
        printf("No :(\n");
    }
    return 0;
}


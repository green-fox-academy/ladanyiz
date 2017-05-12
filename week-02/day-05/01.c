#include <stdio.h>
#include <stdint.h>
#include <string.h>

int is_anagram(char one[], char two[]){

    uint8_t size_one = strlen(one);
    uint8_t size_two = strlen(two);
    uint8_t tmp;
    uint8_t n;
    uint8_t anagram = 1;

	for (uint8_t i = size_one-1; i > 0; i--)
		for (uint8_t j = 0; j < i; j++)
			if(one[j] > one[j+1])
			{
				tmp = one[j];
				one[j] = one[j+1];
				one[j+1] = tmp;
			}

	for (uint8_t i = size_two-1; i > 0; i--)
		for (uint8_t j = 0; j < i; j++)
			if(two[j] > two[j+1])
			{
				tmp = two[j];
				two[j] = two[j+1];
				two[j+1] = tmp;
			}
    
    n = 0;
    do {
        if (one[n] != two[n]) {
            anagram = 0;
        }
        n++;
    } while (n<size_one && anagram==1);

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


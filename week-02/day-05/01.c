#include <stdio.h>
#include <stdint.h>
#include <string.h>

int is_anagram(char one[], char two[]) {

    uint8_t size = strlen(one); // or strlen(two), since they are equal
    uint8_t tmp;
    uint8_t anagram = 1;
    uint8_t i;
    uint8_t j;

	for (i = size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (one[j] > one[j+1])
			{
				tmp = one[j];
				one[j] = one[j+1];
				one[j+1] = tmp;
			}

	for (i = size - 1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (two[j] > two[j+1])
			{
				tmp = two[j];
				two[j] = two[j+1];
				two[j+1] = tmp;
			}

    while (i<size && anagram==1) {
        if (one[i] != two[i]) {
            anagram = 0;
        }
        i++;
    }

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
    } else if (is_anagram(first, second)) {
        printf("Yes, they are!\n");
    } else {
        printf("No :(\n");
    }
    return 0;
}


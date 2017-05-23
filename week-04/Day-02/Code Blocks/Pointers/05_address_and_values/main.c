#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Print out the addresses with and without pointer
print out the values with and without pointer
 */


int main()
{
    int number = 2017;
    float Pi = 3.14;
    char letter = 't';

    int *pNumber = &number;
    float *pPi = &Pi;
    char *pLetter = &letter;

    printf("%p\t%p\t%p\n", pNumber, pPi, pLetter);
    printf("%p\t%p\t%p\n", &number, &Pi, &letter);

    printf("%d\t%.2f\t%c\n", *pNumber, *pPi, *pLetter);
    printf("%d\t%.2f\t%c\n", number, Pi, letter);

    return 0;
}

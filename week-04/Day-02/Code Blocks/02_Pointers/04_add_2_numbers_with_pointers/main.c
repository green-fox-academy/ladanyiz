#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Add two numbers using pointers

*/


int main()
{

    int a  = 20;
    int b = 17;
    int *pA = &a;
    int *pB = &b;

    printf("%d\n", *pA + *pB);

    return 0;
}

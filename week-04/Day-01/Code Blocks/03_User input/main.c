#include <stdio.h>
#include <stdlib.h>

/*
Create a program which ask for a name and an age.
From the age it tells the user when he or she will be 100 years old.
You should only take care of the years (don't bother with the months or days).
*/

#define YEAR 2017

int main()
{
    char name[20];
    int age;

    printf("Please tell me your name: ");
    gets(name);
    printf("And your age: ");
    scanf("%d", &age);

    printf("%s, you will be 100 in %d\n", name, YEAR - age + 100);

    return 0;
}

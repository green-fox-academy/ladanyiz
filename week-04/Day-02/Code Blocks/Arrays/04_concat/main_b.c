#include <stdio.h>
#include <stdlib.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/

#include <string.h>

char *concatenate(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // test
    printf("%d\n%d\n", len1, len2);

    char result[len1 + len2];

    for (int i = 0; i < len1; i++)
        result[i] = str1[i];

    for (int i = 0; i < len2; i++)
        result[len1 + i] = str2[i];

    return result;
}

int main()
{

    char str1[] = "Ladanyi ";
    char str2[] = "Zoltan";

    printf("%s\n", concatenate(str1, str2));

    return 0;
}

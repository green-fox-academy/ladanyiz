#include <stdio.h>
#include <stdlib.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/

#include <string.h>

char *concatenate(char *dest, char *source)
{
    int len1 = strlen(dest);
    int len2 = strlen(source);

    // test
    printf("%d\n%d\n", len1, len2);
    printf("%d\n", len1 + len2 + 1);

    char result[16] = '0';

    // test
    puts(result);
    printf("%d\n", strlen(result));

    int i;
    int j;

    for (i = 0; i != '\0'; i++)
        result[i] = dest[i];

    for (j = 0; j != '\0'; j++)
        result[i + j] = source[j];

    result[i + j] = '\0';

    puts(result);

    return result;
}

int main()
{

    char str1[] = "Ladanyi ";
    char str2[] = "Zoltan";

    printf("%s\n", concatenate(str1, str2));

    return 0;
}

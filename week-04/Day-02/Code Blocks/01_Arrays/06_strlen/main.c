#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function which receives a string as parameter, and returns
// the numbers of characters in the string.
// Don't use the strlen() function!

int string_length(char *string)
{
    int result = 0;
    int i = 0;

    while (string[i] != '\0') {
        result++;
        i++;
    }

    return result;
}

int main()
{
    char str[] = "How long am I?";

    printf("%d\n", string_length(str));

    return 0;
}

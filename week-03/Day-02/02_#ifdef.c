#include <stdio.h>
#include <stdlib.h>

// Define the TOTORO macro which holds the number of students in our class
#define TOTORO 19

int main()
{
// Use the #ifdef and #ifndef macros!

// If the TOTORO macro is not defined print out 32
#ifndef TOTORO
    printf("32\n");
#endif // TOTORO

// If the TOTORO macro is defined print out it's value
#ifdef TOTORO
    printf("TOTORO = %d", TOTORO);
#endif // TOTORO

    return 0;
}

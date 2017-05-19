#include <stdio.h>
#include <stdint.h>

int main() {
    char buffer[255];   // Buffer variable for user input

    //TODO:
    // Get the user's name with scanf
    printf("What is your name?: ");
    scanf("%s", buffer);

    //TODO:
    // Print it out with printf
    printf("Your name is %s\n", buffer);

    return 0;
}

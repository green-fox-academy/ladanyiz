#include <stdio.h>
#include <stdint.h>

int main() {
    char buffer[255];   // Buffer variable for user input

    //TODO:
    // Get the user's name with gets
    printf("What is your name?: ");
    gets(buffer);

    //TODO:
    // Print it out with puts
    printf("Your name is ") ;
    puts(buffer);

    //TODO:
    // Get the user's pet name with getch
    int c;
    int i = 0;
    printf("What is your name?: ") ;
    do {
        c = getchar();
        buffer[i] = c;
        i++;
    } while (c != '\n');

    //TODO:
    // Print it out
    printf("Your name is ") ;
    puts(buffer);

    return 0;
}

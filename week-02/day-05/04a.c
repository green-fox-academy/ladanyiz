#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int main() {

    uint8_t max;
    uint8_t number;
    uint8_t guess;

    printf("GUESS MY NUMBER!\n") ;
    printf("I will think of a number between 1 and 'max'\n");
    printf("max (a positive integer up to 100): ");
    scanf("%d", &max);

    srand(time(NULL));
    number = ((rand() % max) + 1);

    printf("num1: %d\n", number);
    printf("Lets start, you have 5 lives left!\n");
    printf("Your guess: ");
    scanf("%d", &guess);
    printf("guess: %d\n", guess);


    /*for (uint8_t i = 4; i>0 && guess!=number; i--){
        if(guess < number){
            printf("My number is bigger, 1 life lost! ");
        }
        else{
            printf("My number is smaller, 1 life lost! ");
        }
        printf("You have %d lives left.\n", i);
        printf("Your guess: ");
        scanf("%d", &guess);

    }*/

    uint8_t i = 5;

    while ((guess != number) && (i > 0)){
        printf("g:%d,num:%d\n",guess,number);
        if(guess < number){
            printf("My number is bigger, 1 life lost! ");
        }else {
            printf("My number is smaller, 1 life lost! ");
        }
        i--;
        printf("You have %d lives left.\n", i);
        printf("Your guess: ");
        scanf("%d", &guess);
    }

    if(guess == number){
        printf("Congratulations, you guessed it!\n");
    }
    else{
        printf("Sorry, you died :)\n");
    }
    return 0;
}

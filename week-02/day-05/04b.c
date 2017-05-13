#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int main() {

    int max;
    int number;
    int guess;
    int answer;

    printf("GUESS MY NUMBER!\n") ;

    do {
        printf("I will think of a number between 1 and 'max'.\n");
        printf("What shall be the max (up to 100)?  ");
        scanf("%d", &max);

        srand(time(NULL));
        number = (rand() % max) + 1;

        printf("Lets start, you have 5 lives left!\n");
        printf("Your guess: ");
        scanf("%d", &guess);

        for (int lives = 5; lives > 1; lives--){
            if (guess == number){
                break;
            }
            else if (guess > number){
                printf("My number is smaller, you have %d lives left.\n", lives -1);
            }
            else {
                printf("My number is bigger, you have %d lives left.\n", lives -1);
            }
            printf("Your guess: ");
            scanf("%d", &guess);
        }

        if(guess == number){
            printf("Congratulations, you guessed it!\n");
        }
        else{
            printf("Sorry, you died :)\n");
        }
        printf("Shall we play again (1/0)? ");
        scanf("%d", &answer);
    } while ( answer == 1);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

//make it work

int main(){

    printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
    printf("- for it's memory address please press 1\n");
    printf("- for it's current value please press 2\n");
    printf("- to double it's value please press 3\n");

    int choice;
    int number = 42;

    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("%p\n", &number);
            break;
        case 2:
            printf("%d\n", number);
            break;
        case 3:
            printf("%d\n", number *= 2);
            break;
        default:
            printf("Not a valid choice\n");
        }
    }

    return 0;
}

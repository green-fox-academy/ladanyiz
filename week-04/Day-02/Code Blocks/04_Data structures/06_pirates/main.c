#include <stdio.h>

struct pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the sum of the golds of all pirates
int sum_of_gold(struct pirate *pirates, int size)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += pirates[i].gold_count;

    return sum;
}

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the average of the gold / pirate
float average_gold(struct pirate *pirates, int size)
{
    float average = sum_of_gold(pirates, size) / (float)size;

    return average;
}

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the name of the
// richest that has wooden leg
char *richest_with_wooden_leg(struct pirate *pirates, int size)
{
    int gold = 0;
    int index = 0;

    for (int i = 0; i < size; i++) {
        if (pirates[i].has_wooden_leg) {
            if (pirates[i].gold_count > gold) {
                gold = pirates[i].gold_count;
                index = i;
            }
        }
    }

    return pirates[index].name;
}

int main()
{
    struct pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };

    printf("The sum of all the pirates' gold is %d\n", sum_of_gold(pirates, 6));
    printf("The average amount of gold a pirate has is %.2f\n", average_gold(pirates, 6));
    printf("The richest pirate with a wooden leg is %s\n", richest_with_wooden_leg(pirates, 6));

    return 0;
}

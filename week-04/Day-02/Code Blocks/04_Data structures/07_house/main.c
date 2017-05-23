#include <stdio.h>

// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
struct s_house {
    char *address;
    int price;
    int rooms;
    int area;
};

// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
int worth_it(struct s_house *house)
{
    int result = 0;

    if (house->price / house->area <= 400)
        result = 1;

    return result;
}

// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int how_many_are_worth_it(struct s_house *houses, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (worth_it(&houses[i])) {
            count++;
        }
    }

    return count;
}

int main()
{
    struct s_house houses[] = {
        {"I don't know", 90000, 4, 120},    // 750
        {"No idea", 50000, 6, 155},         // 323
        {"Who cares", 63500, 5, 174},       // 365
        {"I don't remember", 47800, 4, 108} // 443
        };

    printf("The number of houses worth to buy is %d\n", how_many_are_worth_it(houses, 4));

    return 0;
}

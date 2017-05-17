#include <stdio.h>
#include <string.h>

// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
struct House {
    char address[30];
    int price;
    int rooms;
    int area;
};

// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
int IsItWorthIt(struct House _house) {

    int worth_it = 0;

    if (_house.price / _house.area <= 400) {
        worth_it = 1;
    }

    return worth_it;
}

// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int HowManyIsWorthIt(struct House* _houses, int size) {

    int num = 0;
    for (int i = 0; i < size; i++) {
        if (IsItWorthIt(_houses[i]) == 1) {
            num++;
        }
    }

    return num;
}

int main() {

    struct House houses[] = {
        {"I don't know", 100000, 4, 120},
        {"No idea", 60000, 6, 155},
        {"Who cares", 73500, 5, 174},
        {"I don't remember", 57800, 4, 108}
        };

    printf("The number of houses worth to buy is %d\n", HowManyIsWorthIt(houses, 4));

    return 0;
}

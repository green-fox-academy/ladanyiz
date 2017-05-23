#include <stdio.h>

enum car_type {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct car {
    enum car_type type;
    double km;
    double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level
void car_printer(struct car _car)
{
    printf("type: ");
    switch(_car.type) {
    case 0:
        printf("VOLVO\n");
        break;
    case 1:
        printf("TOYOTA\n");
        break;
    case 2:
        printf("LAND_ROVER\n");
        break;
    case 3:
        printf("TESLA\n");
        break;
    };

    printf("km: %.0f\n", _car.km);

    if (_car.type != TESLA)
        printf("gas: %.2f\n", _car.gas);

    printf("\n");
}

int main()
{
    struct car cars[] = {
        {VOLVO, 123456, 34},
        {TOYOTA, 234567, 12.4},
        {LAND_ROVER, 23456, 44.2},
        {TESLA, 56789, 0},
    };

    for (int i = 0; i < sizeof(cars) / sizeof(struct car); i++)
        car_printer(cars[i]);

    return 0;
}

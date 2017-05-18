
//NOT PERFECT!!!

#include <stdio.h>

enum CarType {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct Car {
  enum CarType type;
  double km;
  double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level

void CarData(struct Car _car) {
    // printf("Type: %s\n", _car.type);
    printf("Mileage: %.0f\n", _car.km);
    if (_car.type != TESLA) {
        printf("Fuel level: %.1f\n", _car.gas);
    }
    printf("\n\n");
}

int main() {

    struct Car car1 = {VOLVO, 123456, 23.6};
    struct Car car2 = {TOYOTA, 234567, 37.8};
    struct Car car3 = {LAND_ROVER, 98765, 19.4};
    struct Car car4 = {TESLA, 57234, 0.0};

    CarData(car4);
    CarData(car2);
    CarData(car3);
    CarData(car1);

    return 0;
}

#include <stdio.h>

struct RectangularCuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double GetSurface(struct RectangularCuboid _brick) {
    double surface = (_brick.a*_brick.b + _brick.a*_brick.c + _brick.b*_brick.c) * 2;
    return surface;
}

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double GetVolume(struct RectangularCuboid _brick) {
    double volume = _brick.a * _brick.b * _brick.c;
    return volume;
}

int main() {

    struct RectangularCuboid brick = {8.58, 9.76, 10.23};

    printf("Its surface is %.2f\n", GetSurface(brick));
    printf("Its volume is %.2f\n", GetVolume(brick));
    return 0;
}

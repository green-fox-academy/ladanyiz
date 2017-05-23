#include <stdio.h>

struct rectangular_cuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
int GetSurface(struct rectangular_cuboid brick)
{
    int surface = (brick.a * brick.b * 2 + brick.a * brick.c * 2 + brick.b * brick.c * 2);

    return surface;
}

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
int GetVolume(struct rectangular_cuboid brick)
{
    int volume = brick.a * brick.b * brick.c;

    return volume;
}

int main()
{
    struct rectangular_cuboid brick = {10, 10, 10};

    printf("Surface: %d\n", GetSurface(brick));
    printf("Volume: %d\n", GetVolume(brick));

    return 0;
}

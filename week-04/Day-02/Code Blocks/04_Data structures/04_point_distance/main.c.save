#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} point_t;

// TODO:
// Create a function that constructs a Point (returns a pointer to a new point)
// It should take it's x and y coordinate as parameter
point_t *create_point(int x, int y)
{
    point_t *pPoint = malloc(sizeof(point_t));

    pPoint->x = x;
    pPoint->y = y;

    return pPoint;
}

// TODO:
// Create a function that takes 2 Points as pointers and returns the distance between them
double distance(point_t *p1, point_t *p2)
{
    double result = sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));

    return result;
}

int main()
{
    point_t *p1 = create_point(14, 1);
    point_t *p2 = create_point(6, 8);

    printf("The distance between p1 and p2 is %.2f\n", distance(p1, p2));

    free(p1);
    free(p2);

    return 0;
}

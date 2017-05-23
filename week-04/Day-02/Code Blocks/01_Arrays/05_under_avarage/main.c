
// NOT READY!!!

#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function that takes a double array as a parameter, and the length of the array.
// This function should calculate the average of the elements.
double average(double *array, int len)
{
    double sum = 0;

    for (int i = 0; i < len; i++)
        sum += array[i];

    double result = sum / len;

    return result;
}

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It calculates how many elements are under the average, and returns with that.
int under_average(double *array, int len)
{
    int result = 0;

    for (int i = 0; i < len; i++) {
        if (array[i] < average(array, len)) {
            result++;
        }
    }

    return result;
}

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It allocates a new array, and loads into it the elements which are under the average.
// It returns a pointer to the new array.
char *under_average_array(double *array, int len)
{
    double result[under_average(array, len)];

    for (int i = 0; i < len; i++) {
        if (array[i] < average(array, len)) {
            result[i] = array[i];
        }
    }

    return result;
}

int main()
{

    return 0;
}

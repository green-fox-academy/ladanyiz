#include <stdio.h>
#include <math.h>

/* Write a non void function which returns the value of PI, so the following number:
3.14159
Try it out in the main function by printing out the result of the pi generator function!
*/
float PI_generator(){

    float nPI = M_PI;

    return nPI;
}

int main(){

    printf("%.5f\n", PI_generator());

    return 0;
}

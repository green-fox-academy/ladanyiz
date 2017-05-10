#include <stdio.h>
#include <stdint.h>

/* Write a non void function which has a parameter (let's say for example x).
The function then returns the "xth" fibonacci number.
What the hack is a fibonacci number? Search it on wikipedia!
*/
int Fibonacci(int x) {

    if(x == 0) {
        return 0;
    }
    if(x == 1 || x == 2) {
        return 1;
    }

    int n;
    int result = 0;
    int prev_result = 1;
    int prev_prev_result = 1;

    for (n = 2; n < x; n++) {
        result = prev_prev_result + prev_result;
        prev_prev_result = prev_result;
        prev_result = result;
    }

return result;
}

int main(){

    printf("%d\n", Fibonacci(6));

return 0;
}

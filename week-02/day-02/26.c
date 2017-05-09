#include <stdio.h>

int main() {
	// Write a program that prints the numbers from 1 to 100.
	// But for multiples of three print "Fizz" instead of the number
	// and for the multiples of five print "Buzz".
	// For numbers which are multiples of both three and five print "FizzBuzz".
	int n = 1;
	for (n; n < 101; n++) {
        if (n%3 == 0 && n%5 == 0) {
            printf("FizzBuzz\n");
        }
        else if (n%3 == 0) {
            printf("Fizz\n");
        }
        else if (n%5 == 0) {
            printf("Buzz\n");
        }
        else {
            printf("%d\n", n);
        }
    }
	return 0;
}

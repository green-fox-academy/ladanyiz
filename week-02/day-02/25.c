#include <stdio.h>

int main() {
	// print the even numbers till 20
	int n = 1;
	while (n < 21) {
        if (n%2 == 0) {
            printf("%d\n", n);
        }
        n++;
	}
	return 0;
}

#include <stdio.h>
#include <stdint.h>

int main() {
	int a = 654;
	uint64_t b = 654987312;
	// Tell if the remainder of b divided by a is 3
    if (b % a == 3) {
        printf("%d is 3\n", b % a);
    } else {
        printf("%d is not 3\n", b % a);
    }
	return 0;
}

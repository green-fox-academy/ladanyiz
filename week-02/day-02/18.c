#include <stdio.h>
#include <stdint.h>

int main() {
	uint16_t number = 254;
	// if number can't be represented with 8bits
	// print 'longer than 8bits' otherwise print 'ok'
	if (number > 255) {
        printf("Longer than 8 bits\n");
	}
	else {
        printf("OK\n");
	}
	return 0;
}

#include <stdio.h>
#include <stdint.h>

int main() {

	uint8_t ac = 8;
	uint8_t time = 120;
	uint8_t out;
	// if ac is divisible by 4
	// and time is not more than 200
	// set out to 0b100
	if (ac%4 == 0) {
        if (time <= 200) {
            printf("out is 0b100, decimal %d\n", out = 0b100);
        }
	// if time is more than 200
	// set out to 0b010
        else {
            printf("out is 0b010, decimal %d\n", out = 0b010);
        }
	}
	// otherwise set out to 0b001
	else {
            printf("out is 0b001, decimal %d\n", out = 0b001);
	}
	return 0;
}

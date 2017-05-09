#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t number = 254;
	uint8_t result;

	result = number + 23;
	// Check the result with printf
	printf("%d", result);

 	// What happened?!
 	// Overflow, the result cannot fit in an 8-bit int variable.

	// Try again with different datatype
	uint16_t result_16 = number + 23;

	// Check the result with printf
	printf("\n%d", result_16);

	// What happened and why?
    // It worked well since the result is a 16-bit integer.
	//----------------------------------------

	int8_t number_negative = number;
	// Check the result with printf
    result = number_negative + 23;
	printf("\n%d", result);

	// What happened and why?
	// The same as with unsigned, not a negative number
    return 0;
}

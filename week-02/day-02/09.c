#include <stdio.h>

int main() {
	int i = 53625;
	// tell if it has 11 as a divisor
	if (i%11 == 0){
        printf("%d is divisible by 11", i);
	}
	else {
        printf("%d is not divisible by 11", i);
	}
	return 0;
}

#include <stdio.h>

int main() {
	int h1 = 350;
	int h2 = 200;
	// tell if the double of h2 is bigger than h1
	if (h2*2 > h1){
        printf("The double of %d is bigger than %d", h2, h1);
	} else {
        printf("The double of %d is smaller than %d", h2, h1);
	}
	return 0;
}

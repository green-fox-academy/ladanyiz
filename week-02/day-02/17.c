#include <stdio.h>
#include <math.h>

int main() {
	float w = 24;
	int out = 0;
	// if w is even increment out by one
	if (fmod(w,2) == 0) {
        printf("%d\n", ++out);
	}
	return 0;
}

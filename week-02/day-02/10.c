#include <stdio.h>

int main() {
	int j1 = 10;
	int j2 = 3;
	// tell if j1 is higher than j2 squared and smaller than j2 cubed
	if (j1 <= j2*j2){
        printf("%d is not bigger than %d squared", j1, j2);
	}
	else if(j1 > j2*j2 && j1 <= j2*j2*j2){
        printf("%d is bigger than %d squared, but not bigger than %d cubed", j1, j2, j2);
	}
	else {
        printf("%d is bigger than %d cubed", j1, j2);
	}
	return 0;
}

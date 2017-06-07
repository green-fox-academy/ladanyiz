#include <stdio.h>
#include <stdint.h>

void int_to_bin_digit(int in, int count)
{
	uint64_t mask = 1U << count;
	printf("%X\n", in & mask);
	int i;
	for (i = 0; i < count; i++) {
		int result = (in & mask) ? 1 : 0;
		printf("%d", result);
		in = in << 1;
	}
}

int main()
{
	int_to_bin_digit(16, 10);
	return 0;
}

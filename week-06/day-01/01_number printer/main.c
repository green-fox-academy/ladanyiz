#include <stdio.h>
#include <stdint.h>

void printf_numbers(uint32_t from, uint32_t to)
{
	for (int i = from; i < to; i++)
		printf("%u,", i);
}

int main()
{
	printf_numbers(2147483600, 2147484600);
	return 0;
}

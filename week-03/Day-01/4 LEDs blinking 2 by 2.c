#include <avr/io.h>			// This header contains the definitions for the io registers

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

int main(void)
{
	DDRB |= 1 << DDRB0;
	DDRB |= 1 << DDRB1;
	DDRB |= 1 << DDRB2;
	DDRB |= 1 << DDRB3;
	
	PORTB |= 1 << PORTB0;
	PORTB |= 1 << PORTB2;

	while (1) {
		PINB |= 1<<PINB0;
		PINB |= 1<<PINB1;
		PINB |= 1<<PINB2;
		PINB |= 1<<PINB3;
		_delay_ms(500);
	}
}
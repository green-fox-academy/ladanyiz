#include <avr/io.h>			// This header contains the definitions for the io registers

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

int main(void)
{
	DDRB |= 0b00001111;
	/*DDRB |= 1<<DDRB1;
	DDRB |= 1<<DDRB2;
	DDRB |= 1<<DDRB3;*/

	while (1) {
		uint8_t i;
		for (i = 0; i < 4; i++){
			PINB |= 1<<i;
			_delay_ms(150);
			PINB |=	1<<i;
		}
		for (i = 2; i > 0; i--){
			PINB |= 1<<i;
			_delay_ms(150);
			PINB |=	1<<i;
		}
	}
}
/*
 * Turning on_off LED depending on counter value.c
 *
 * Created: 2017. 05. 10. 15:03:49
 * Author : Z
 */ 

#include <avr/io.h>

void init()
{
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 0b00000101 ; // 0000 0000 | 0000 0101 -> 0000 0101

	// Set the PB5 LED pin to output
	DDRB |= 1 << DDRB5 ; 
}

int main(void)
{
	// Don't forget to call the init function!
	init();

	while (1) {
		// If TC0 counter overflow occurred (TOV0 flag is set) toggle the LED and write "1" to that flag (this will clear it, i know, it's confusing, but this is how it works)
		if ((TIFR0 & 0b00000001) == 1) { // ???? ???? & 0000 0001 -> 0000 0000 vagy 0000 0001
			PINB |= 1 << PINB5 ;
			TIFR0 |= 1 << TOV0 ;
		}
	}
}
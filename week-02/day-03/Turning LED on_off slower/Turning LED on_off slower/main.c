/*
 * Turning LED on_off slower.c
 *
 * Created: 2017. 05. 10. 16:20:43
 * Author : Z
 */ 

#include <avr/io.h>
#include <stdint.h>

void init()
{
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 1 << CS02;
	TCCR0B |= 1 << CS00;

	// Set the PB5 LED pin to output
	DDRB = 1 << DDRB5;
}

int main(void)
{
	// Create a variable which will be a counter variable, initialize it with 0.
	uint8_t cntr = 0;
	
	// This will be the maximal value of our counter
	const uint8_t cntr_max = 30;

	// Don't forget to call the init function!
	init() ;
	
	while (1)
	{
		// Check the TOV0 overflow flag. If an overflow happened do the following:
		if ((TIFR0 & 0x01) == 1) {
			
			//	- clear the overflow flag
			TIFR0 |= 1 << TOV0;
			
			//  - check the counter variable
			//	- if it is smaller than the maximal value, than increment it!
			
			if (cntr < cntr_max) {
				cntr++;
			}
			
			//	- else set it to 0, and toggle the LED
			else {
				cntr = 0;
				PINB |= 1 << PINB5;
			}
		}
	}
}
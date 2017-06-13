#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "freq_meas.h"
#define  MAX_COUNTER_VALUE	65535

volatile uint8_t overflow_counter = 0;
volatile uint8_t rising_edge_counter = 0;
volatile uint16_t first_timer_value = 0;
volatile uint16_t last_timer_value = 0;

// TODO:
// Write the interrupt handlers

ISR(TIMER1_CAPT_vect)
{	
	if (rising_edge_counter == 0) {			// so this is the first rising edge
		first_timer_value = ICR1;
		rising_edge_counter++;
	} else if (rising_edge_counter == 1) {	// so this is the second rising edge
		last_timer_value = ICR1;
		rising_edge_counter++;
	}
}

ISR(TIMER1_OVF_vect)
{
	if (rising_edge_counter < 2)			// count overflows only until the second rising edge
		overflow_counter++;
}

void freq_meas_init()
{
	/**************
	 * TC1 CONFIG *
	 **************/
	// TODO:
	// Configure the TC1 timer properly :)
	
	// Set timer to normal operation
	// Actually everything can be set to zero here
	TCCR1A = 0;
	
	// Set noise cancelling and rising edge detection 
	TCCR1B |= (1 << ICNC1) | (1 << ICES1);
	
	// Set prescaler to 256
	TCCR1B |= 4; // last three bits are 100, clk/256, Tclk = (1 / 16 MHz (the CPU frequency) * 256 = 1 / 16000000 * 256 = 0.000016 s  
	
	// Enable input capture and timer overflow interrupts
	TIMSK1 |= (1 << ICIE1) | (1 << TOIE1);
}

// TODO:
// Write this function. It returns the measured frequency in Hz
float get_freq()
{
	uint32_t steps = overflow_counter * MAX_COUNTER_VALUE + last_timer_value - first_timer_value;	// the number of counter clock cycles in one phase
	float Tclk = 0.000016;		// 1 counter clock cycle in seconds
	float T = Tclk * steps;		// input phase time in seconds
	float Hz = 1 / T;	
	return Hz;
}
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "freq_meas.h"

volatile uint8_t overflow_counter = 0;
volatile uint8_t number_of_overflows = 0;
volatile uint16_t first_timer_value = 0;
volatile uint16_t last_timer_value = 0;

// TODO:
// Write the interrupt handlers

ISR(TIMER1_CAPT_vect)
{	
	first_timer_value = last_timer_value;
	last_timer_value = ICR1;
	number_of_overflows = overflow_counter;
	overflow_counter = 0;
}

ISR(TIMER1_OVF_vect)
{
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
	// Actually everything can be set to zero here, and this is also the default state
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
	uint32_t steps = number_of_overflows * MAX_COUNTER_VALUE + last_timer_value - first_timer_value;	// the number of counter clock cycles in one period
	float Tclk = 0.000016;		// 1 counter clock cycle in seconds
	float T = Tclk * steps;		// input period time in seconds
	float Hz = 1 / T;
	printf("first counter value: %u\n", first_timer_value);
	printf("last counter value: %u\n", last_timer_value);	
	return Hz;
}
/*
 * PWM.c
 *
 * Created: 2017. 06. 12. 10:07:39
 *  Author: Z
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
//#include <avr/delay.h>


void pwm_init()
{
	//This time using TC2!
	
	// Set non-inverting fast PWM mode with TOP = 0xFF
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
	
	// Set prescaler to 64 and with that the timer on 
	TCCR2B |= 1 << CS22;
	
	// Set the PB3 (OC2A) pin to output
	DDRB |= 1 << DDRB3;
}

uint8_t set_duty_cycle(uint8_t percent)
{
	uint8_t dc = 255 * percent / 100;
	return dc;
}
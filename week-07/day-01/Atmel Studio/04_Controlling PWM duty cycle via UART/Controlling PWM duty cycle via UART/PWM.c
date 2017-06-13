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
	// Set prescaler to 64 and with that the timer on
	TCCR0B |= 3;

	// Set Fast PWM mode with TOP = OCR0A
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	
	// Set non-inverted PWM
	TCCR0A |= 1 << COM0A1;
	
	// Set the PD6 (OC0A) pin to output
	DDRD |= 1 << DDRD6;
}

uint8_t set_duty_cycle(uint8_t percent)
{
	uint8_t dc = 255 * percent / 100;
	return dc;
}
/*
 * Dimming a LED in Fast PWM mode.c
 *
 * Created: 2017. 06. 12. 10:05:27
 * Author : Z
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

int main(void)
{
	pwm_init();
	
	while (1) {
		for (uint8_t i = 0; i < 101; i++) {
			OCR0A = set_duty_cycle(i);
			_delay_ms(15);
		}
		for (uint8_t i = 99; i > 0; i--) {
			OCR0A = set_duty_cycle(i);
			_delay_ms(15);
		}
//		OCR0A = set_duty_cycle(50);
	}
}


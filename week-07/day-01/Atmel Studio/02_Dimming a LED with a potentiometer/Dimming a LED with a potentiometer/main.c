/*
 * Dimming a LED with a potentiometer.c
 *
 * Created: 2017. 06. 12. 12:42:12
 * Author : Z
 */ 

#include <avr/io.h>
#include "PWM.h"
#include "ADC_driver.h"

int main(void)
{
    pwm_init();
	ADC_Init();
	
	while (1) {
		OCR0A = ADC_Read() >> 2; // because the ADC data is 10 bits, and we need 8
    }
}


/*
 * Open loop control.c
 *
 * Created: 2017. 06. 15. 11:30:11
 * Author : Z
 */ 

#include <avr/io.h>
#include <stdio.h>
#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function
#include <avr/interrupt.h>
#include "AC_driver.h"
#include "ADC_driver.h"
#include "freq_meas.h"
#include "PWM.h"
#include "UART_driver.h"

void system_init()
{
	AC_driver_init();
	ADC_Init();
	freq_meas_init();
	pwm_init();
	UART_init();
	sei();
}

int main(void)
{
	system_init();
	
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM((void *)UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, (void *)UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	// Try printf
	printf("Startup...\r\n");
    
	while (1) 
    {
		uint8_t duty_c = ADC_Read() >> 2;
		OCR2A = duty_c;										//TC2 is used
		printf("Duty cycle: %d%%\t\t", duty_c * 100 / 255);
		printf("RPM: %.0f\n", get_rpm());
		_delay_ms(1000);
    }
	return 0;
}


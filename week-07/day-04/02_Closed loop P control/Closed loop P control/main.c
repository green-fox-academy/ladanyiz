/*
 * Closed loop P control.c
 *
 * Created: 2017. 06. 15. 14:14:53
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
#define MAX_RPM		4500
#define P			0.3
#define MIN_OUTPUT	0
#define MAX_OUTPUT	100

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
	
	while (1)
	{
		float ref = (ADC_Read() >> 2) / (float)255 * MAX_RPM;
//		float ref = 1800;
		printf("ref: %.0f\t\t", ref);
		
		float feedback = get_rpm();
		printf("feedback: %.0f\t\t", feedback);
		
		float err = ref - feedback;
		printf("err: %.0f\t\t", err);
		
		int16_t output = (int16_t)(P * err);		
		
		if (output < MIN_OUTPUT)
			output = MIN_OUTPUT;
		else if (output > MAX_OUTPUT)
			output = MAX_OUTPUT;
		printf("Duty cycle: %d%%\t\t", output);
		
		uint8_t reg_data = set_duty_cycle((uint8_t)output);
		OCR2A = reg_data;										//TC2 is used
		
 		printf("RPM: %.0f\n", get_rpm());
		_delay_ms(10);
	}
	return 0;
}


/*
 * Closed loop PI control.c
 *
 * Created: 2017. 06. 15. 16:47:47
 * Author : Z
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
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
#define I			0.01
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
/*
int kbhit(void)
{
	return ((UCSR0A & (1<<RXC0)) != 0);
}

float get_ref()
{
	char *str = NULL;
	gets(str);
	printf("string: %s\n", str);
	float value = atof(str);
	printf("value: %.0f\n", value);
	if (value < 0)
		value = 0;
	else if (value > MAX_RPM)
		value = MAX_RPM;
	return value;
}
 */
int main(void)
{
	float integral = 0;
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
//		float ref = 800;
/*		if (kbhit())
			ref = get_ref();
		printf("ref: %.0f\t\t", ref);
 */		
		float feedback = get_rpm();
		printf("feedback: %.0f\t\t", feedback);
		
		float err = ref - feedback;
		printf("error: %.0f\t\t", err);
		
		integral += err;
		
		int16_t output = (int16_t)(P * err) + (I * integral);
		
		if (output < MIN_OUTPUT) {
			output = MIN_OUTPUT;
			integral -= err;
		} else if (output > MAX_OUTPUT) {
			output = MAX_OUTPUT;
			integral -= err;
		}
		printf("Duty cycle: %d%%\t\t", output);
		
		uint8_t reg_data = set_duty_cycle((uint8_t)output);
		OCR2A = reg_data;										//TC2 is used
		
		printf("RPM: %.0f\n", get_rpm());
		_delay_ms(10);
	}
	return 0;
}



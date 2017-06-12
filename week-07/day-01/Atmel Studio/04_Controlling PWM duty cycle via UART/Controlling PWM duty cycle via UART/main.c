/*
 * Controlling PWM duty cycle via UART.c
 *
 * Created: 2017. 06. 12. 13:43:33
 * Author : Z
 */ 

#include "ADC_driver.h"
#include "UART_driver.h"
#include "PWM.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

void SystemInit() {
	pwm_init();
	ADC_Init();
	UART_Init();
	// Enable interrupts globally, UART uses interrupts
	sei();
}

int8_t input_ok(char *input)
{
	char message[25] = "Not a percentage number";
	
	if ((strlen(input) == 0) || (strlen(input) > 4)) {
		printf("%s\n", message);
		return -1;
	} else if (strlen(input) == 1) {
		printf("%s\n", message);
		return -1;
	} else if (strlen(input) == 2) {
		if ((input[0] < '1') || (input[0] > '9')) {
			printf("%s\n", message);
			return -1;
		}
	} else if (strlen(input) == 3) {
		if ((input[0] < '1') || (input[0] > '9')){
			printf("%s\n", message);
			return -1;
		} else if ((input[1] < '0') || (input[1] > '9')) {
			printf("%s\n", message);
			return -1;
		}
	} else if (strlen(input) == 4) {
		if (strcmp(input, "100") != 0) {
			printf("%s\n", message);
			return -1;
		}
	}
	return 1;
}
 
int main(void)
{
    SystemInit();
	
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	char buffer[256];
	int16_t data;

	while (1) {
		printf("Enter percentage:\n");
		gets(buffer);
		puts(buffer);
		printf("strlen=%d\n", strlen(buffer));
		
		if (input_ok(buffer) == 1) {
			
			data = atoi(buffer);
		
			data = data * 255 / 100;
		
			OCR0A = data;
		}
    }
	return 0;
}


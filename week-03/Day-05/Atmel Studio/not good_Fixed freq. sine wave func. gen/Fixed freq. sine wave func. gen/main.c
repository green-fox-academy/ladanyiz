/*
 * Fixed freq. sine wave func. gen.c
 *
 * Created: 2017. 05. 19. 13:30:55
 * Author : Z
 */ 

#include "ADC_driver.h"
#include "UART_driver.h"
#include "MCP4821_driver.h"
#include "sine_gen.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

#define LED_DDR			DDRB
#define LED_DDR_POS		DDRB5
#define LED_PIN			PINB
#define LED_PIN_POS		PINB5
#define LED_PORT		PORTB
#define LED_PORT_POS	PORTB5

volatile uint8_t cntr = 0;

void SystemInit() {
	// Initialize the LED pin as output
	LED_DDR |= 1 << LED_DDR_POS;
	// Set the LED to off as default
	LED_PORT &= ~(1 << LED_PORT_POS);

	// Call the ADC driver init function
	ADC_Init();

	// Call the UART driver init function
	// Keep in mind that the UART will run at 115200 baud/sec
	UART_Init();
	
	MCP4821_Init();
	
	SineGenInit();

	// Enable interrupts globally, UART uses interrupts
	sei();
}

int main(void) {
	
	uint16_t adc_data;
	
	// Don't forget to call the init function :)
	SystemInit();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	
	char temp[8];
	
	printf("\nFIXED FREQUENCY SINE WAVE FUNCTION GENERATOR\n\n");
	printf("Give me the range of the sine wave between 0 and 4.096: ");
	
	while (1) {
		gets(temp);
	
		ampl = atof(temp) / 2;
	
		if (ampl < 0) {
			ampl = 0;
		} else if (ampl > 2.048) {
			ampl = 2.048;
		}
	
		adc_data = ADC_Read();
		UART_SendCharacter(adc_data >> 2);
	}
	
}


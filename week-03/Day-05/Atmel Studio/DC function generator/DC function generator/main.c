/*
 * DC function generator.c
 *
 * Created: 2017. 05. 18. 17:13:22
 * Author : Z
 */ 

#include "ADC_driver.h"
#include "UART_driver.h"
#include "MCP4821_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

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

	// Enable interrupts globally, UART uses interrupts
	sei();
}

int main(void) {
	
	char temp[8];
	uint16_t adc_data;

	// initialize DAC data
	MCP4821_Data_t DAC_data;
	DAC_data.start_zero = 0;
	DAC_data.dont_care = 0;
	DAC_data.gain = 0;	// gain = 2x
	DAC_data.shutdown = 1; // do not shutdown
	DAC_data.data = 0;

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
	
	printf("\nD C   F U N C T I O N   G E N E R A T O R\n\n");
	printf("What voltage shall I generate? Enter a number, preferably between 0 and 4.096: ");

	
	while(1) {
		
		if (rx_buffer.read_ptr != rx_buffer.write_ptr) {
						
			gets(temp);	
			
			double volt = atof(temp);
				
			if(volt < 0) {
				volt = 0;
			} else if(volt > 4.096) {
				volt = 4.096;
			}
	
			DAC_data.data = (int16_t)volt * 4095 / 4.095;
	
			// Test
			// printf("\nData: %d", DAC_data.data);	

			// Send the data structure
			MCP4821_SendData(&DAC_data);		
		}
		
		adc_data = ADC_Read();

		UART_SendCharacter(adc_data >> 2);
	}
	
}
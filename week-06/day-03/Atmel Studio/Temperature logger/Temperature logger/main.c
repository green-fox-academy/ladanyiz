/*
 * Temperature logger.c
 *
 * Created: 2017. 06. 08. 10:52:53
 * Author : Z
 */ 
#include "TC74_driver.h"
#include "UART_driver.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

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

void system_init()
{
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 0b00000101 ; // 0000 0000 | 0000 0101 -> 0000 0101

	// Set the PB5 LED pin to output
	DDRB |= 1 << DDRB5 ;

	//TODO
	// Call the TWI driver init function
	TWI_init();
	
	//TODO
	//Init the uart
	UART_init();
	
	sei();	//enable interrupts
}

int main(void)
{

	// Don't forget to call the init function :)
	system_init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	
	uint8_t cntr = 0;
	uint8_t const max_cntr = 20;
	uint8_t temp;
	
	// Infinite loop
	while (1) {
		//TODO
		//Write the temperature frequently.
		
		//TODO
		//Advanced: Don't use delay, use timer.

		//TODO
		//Blink the led to make sure the code is running
		
		if ((TIFR0 & 1) == 1)  {
			TIFR0 |= 1 << TOV0 ;
			if (cntr < max_cntr) {
				cntr++;
			} else {
				cntr = 0;
				PINB |= 1 << PINB5;
				temp = read_temp(TC_ADDRESS);
				printf("%d\n", temp);
			}
		}			
	}
}
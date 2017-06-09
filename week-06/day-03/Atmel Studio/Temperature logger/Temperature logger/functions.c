/*
 * functions.c
 *
 * Created: 2017. 06. 08. 10:56:39
 *  Author: Z
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "TC74_driver.h"
#include "UART_driver.h"
#include "functions.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

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


void start_screen()
{
	printf("                   Temperature logger\n");
	printf("==========================================================\n");
	printf("Commands:\n");
	printf("h\tShow the command list\n");
	printf("e\tExit from the program\n");
	printf("l\tList available ports\n");
	printf("p\tSet port name\n");
	printf("w\tSet name of file to write\n");
	printf("o\tOpen port\n");
	printf("s\tStart logging / Stop logging\n");
	printf("c\tClose port\n");
	printf("r\tSet name of file to read\n");
	printf("a\tCalculate average in given period\n");
	printf("==========================================================\n\n");
}
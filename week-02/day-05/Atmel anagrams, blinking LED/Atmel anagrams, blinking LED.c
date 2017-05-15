#include <avr/io.h>			// This header contains the definitions for the io registers
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

void UART_Init()
{
	// Write this function
	// See the data sheet on page 246 for hints and table 25-9.
	//---------------------------------
	//TODO:
	// At first set the baud rate to 9600
	// The CPU clock frequency is 16MHz
	UBRR0H = 103 >> 8;
	UBRR0L = 103;

	//TODO:
	// Set the following frame format: 8N1
	// Nothing to do, set by default :)
	
	//TODO:
	// Enable TX
	UCSR0B |= 1 << TXEN0;

	//TODO:
	// Enable RX
	UCSR0B |= 1 << RXEN0;
	
	//set PB5 as output
	DDRB |= 1<<DDRB5;

}

void UART_SendCharacter(char character)
{
	// Write this function, which can send a character through UART with polling method
	// See page 247 of the data sheet for hints, be aware that the code in the data sheet has a problem :)
	//---------------------------------
	//TODO:
	// Wait for empty buffer
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	//TODO:
	// Put data to buffer
	UDR0 = character;

}

char UART_GetCharacter()
{
	// Write this function, which waits for a character and returns when one is received
	// See page 249 of the data sheet for hints, be aware that the code in the data sheet has a problem :)
	//---------------------------------
	//TODO:
	// Wait for data received
	while ( !( UCSR0A & (1<<RXC0)) );
	
	//TODO:
	// Get data from buffer
	return UDR0;
}

void capital(char input[]){
	for (uint8_t i = 0; i < strlen(input); i++)
	input[i] = toupper(input[i]);
}

void arrange(char input[]){
	uint8_t tmp;
	for (uint8_t i = strlen(input)-1; i > 0; i--)
		for (uint8_t j = 0; j < i; j++)
			if(input[j] > input[j+1]){
				tmp = input[j];
				input[j] = input[j+1];
				input[j+1] = tmp;
			}
}

int is_anagram(char one[], char two[]){

	capital(one);
	arrange(one);

	capital(two);
	arrange(two);

	uint8_t anagram = 1;

	if ((strcmp(one, two)) != 0)
	anagram = 0;

	return anagram;
}

void blink_once(){
	PORTB |= 1<<PORTB5;
	_delay_ms(500);
	PORTB &= ~(1<<PORTB5);
}

void blink_twice(){
	/*PORTB |= 1<<PORTB5;
	_delay_ms(250);
	PORTB &= ~(1<<PORTB5);
	_delay_ms(250);
	PORTB |= 1<<PORTB5;
	_delay_ms(250);
	PORTB &= ~(1<<PORTB5);*/
	for (uint8_t i = 0; i < 4; i++){
		PINB |= 1<<PINB5;
		_delay_ms(250);
	}
}

int main(void)
{
	//Don't forget to call the init function :)
	UART_Init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	char first[20];
	char second[20];

	printf("ARE THEY ANAGRAMS?\r\n");
	while(1){
		printf("First word: ");
		gets(first);
		printf("%s\r\n", first);
		printf("Second word: ");
		gets(second);
		printf("%s\r\n", second);
		if (strlen(first) != strlen(second)){
			printf("They are not the same length, so obviously not!\r\n");
			blink_twice();
		}
		else if (is_anagram(first, second) == 1){
			printf("Yes, they are!\r\n");
			blink_once();
		}
		else {
			printf("No :(\r\n");
			blink_twice();
		}
	}
}
#include <avr/io.h>			// This header contains the definitions for the io registers
#include <stdint.h>
#include <stdio.h>

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function
#include <time.h>			// for the RNG
#include <avr/interrupt.h>

volatile uint8_t answer = 0;
volatile uint16_t counter = 0;

ISR(PCINT0_vect){
	if (counter % 2 == 0)
		answer = 1;
	counter++;
}

void button_init(){
	// Set the PCINT7 bit of PCMSK0 register. This will enable the interrupts from the button (PB7=PCINT7)
	PCMSK0 |= 1 << PCINT7 ;
	
	// Enable pin interrupt on change 0 interrupts. This will enable PCINT0, PCINT1, PCINT2 ... PCINT7 interrupts.
	PCICR |= 1 << PCIE0 ;

	// Finally, enable the interrupts globally
	sei();

	// Set PB5 as output, this is the LED pin
	DDRB |= 1 << DDRB5 ;
}

void clock_init(){
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 1 << CS02;
	TCCR0B |= 1 << CS00;
}

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

void countdown(){
	// Create a variable which will be a counter variable, initialize it with 0.
	uint16_t cntr = 0;
	
	// This will be the maximal value of our counter
	const uint16_t cntr_max = 500;
	
	uint8_t i=9;
	
	while ((cntr < cntr_max) && (answer == 0)) {
		// Check the TOV0 overflow flag. If an overflow happened do the following:
		if ((TIFR0 & 0x01) == 1) {
			
			//	- clear the overflow flag
			TIFR0 |= 1 << TOV0;
			cntr++;
			
			if(cntr%50 == 0){
				printf("%d  ",i);
				i--;
			}
		}
	}
}

int main(void)
{
	//Don't forget to call the init function :)
	button_init();
	clock_init();
	UART_Init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	int max;
	int number;
	int guess;

	printf("GUESS MY NUMBER!\r\n") ;

	do {
		answer = 0;
		printf("\r\nI will think of a number between 1 and 'max'.\r\n");
		printf("What shall be the max (up to 100)?  \r\n");
		scanf("%d", &max);

		srand(time(NULL));
		number = (rand() % max) + 1;

		printf("Guess this number between 1 and %d, you have 5 lives left!\r\n", max);
		printf("Your guess: ");
		scanf("%d", &guess);
		printf("%d\r\n", guess);

		for (int lives = 5; lives > 1; lives--){
			if (guess == number){
				break;
			}
			else if (guess > number){
				printf("My number is lower, you have %d lives left.\r\n", lives -1);
			}
			else {
				printf("My number is higher, you have %d lives left.\r\n", lives -1);
			}
			printf("Your guess: ");
			scanf("%d", &guess);
			printf("%d\r\n", guess);
		}

		if(guess == number){
			printf("Congratulations, you guessed it!\r\n");
		}
		else{
			printf("Sorry, you died :)\r\n");
			printf("My number is %d\r\n", number);
		}
		printf("Push the button if you want to play again. \r\n");
		countdown();
	} while ( answer == 1);
}
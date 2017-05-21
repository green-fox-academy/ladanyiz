#include "sine_gen.h"
#include "MCP4821_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <math.h>

volatile uint8_t cntr;
const uint8_t cntr_max = 32;
volatile float pi = M_PI;
volatile int n = 30;

ISR(TIMER0_COMPA_vect) {
	if (cntr < cntr_max) {
		cntr++;
		} else {
		cntr = 0;
		DAC_data.data = sin(2*pi / n) * ampl + 2;
		if (n > 1) {
			n--;
			} else {
			n = 30;
		}
		MCP4821_SendData(&DAC_data);
	}
}

void SineGenInit() {
    // Initialize variables
    cntr = 0;
    // Initialize dac_data
    DAC_data.start_zero = 0;
    DAC_data.dont_care = 0;
    DAC_data.gain = 0;		//2x
    DAC_data.shutdown = 1;	// not shutdown
    DAC_data.data = 0x000;

    // Clock init
    // TCCR0B |= 0b00000101;
    // TCCR0B |= 0x05;
    TCCR0B |= 1 << CS02;
    TCCR0B &= ~(1 << CS01);
    TCCR0B |= 1 << CS00;

    // Set OC register to a default value
    TCCR0A |= 1 << WGM01;
    OCR0A = 255;

    // Enable OCR0A interrupt
    TIMSK0 |= 1 << OCIE0A;
}

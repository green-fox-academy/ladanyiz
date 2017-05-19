#include "ADC_driver.h"
#include <avr/io.h>
#include <stdint.h>

void ADC_Init() {
    // TODO:
    // Set the reference voltage to AVcc.
	ADMUX |= 1 << REFS0; // We need 0 and 1 in REFS1 and REFS0 respectively, 0 is default, no need to set

    // TODO:
    // Set the data format to right adjusted, so the bottom 8bits will be in ADCL register
	// Default is 0, we need 0, no need to set

    // TODO:
    // Set the used channel. Use the definitions from ADC_driver.h!
	ADMUX |= ADC_CH; // |= 0000 0000

    // TODO:
    // Set the prescaler. Use the definitions from ADC_driver.h!
	ADCSRA |= ADC_ADPS; // |= 0000 0111

    // TODO:
    // Enable the ADC peripheral
	ADCSRA |= 1 << ADEN;
}

uint16_t ADC_Read() {
    // TODO:
    // Start a conversion with ADSC bit setup
	ADCSRA |= 1 << ADSC;
	// PRADC &= ~(1 << PRR); // Data Sheet mentions this...

    // TODO:
    // Wait for the conversion to finish by checking ADSC bit
	while(ADCSRA & (1 << ADSC));

    // TODO:
    // return with the read data, use the "ADC" register!
	return ADC;
}
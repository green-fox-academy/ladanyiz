#include <avr/io.h>
#include "AC_driver.h"
#include "freq_meas.h"

void AC_driver_init()
{
	/*************
	 * AC CONFIG *
	 *************/
	// TODO:
	// Disable the digital input buffers on AN0 and AN1 to reduce power consumption.
	// See the DIDR1 register description for more info.
	DIDR1 = 3;			// 0000 0011

	// TODO:
	// Connect the AC output to the AC0 pin.
	// The datasheet is screwed up. It says "Analog Comparator Control and Status Register C", meanwhile the name of this register is "ACSR0",
	// but in the avr/io.g header this register can be reached with the "ACSRB" macro.
	ACSRB = 1;			// 0000 0001
	// TIFR1 |= 1 << ICF1;	//just to be sure, because changing the capture input can trigger an interrupt, this clears the flag

	// TODO:
	// Configure the rest settings properly :)
	// AC output connected to TC1 input capture
	ACSR = 0;	// just to make sure I guess
	// Set analog comparator input capture enable
	ACSR |= 1 << ACIC;
}

// TODO:
// Write this function. It returns the measured rotation speed in RPM
float get_rpm()
{
	return get_freq() * 8 * 60;	// Frequency here means how many ventilator blades pass before the sensor in one second.
}								// We have to multiply by 8 to get one whole ventilator revolution, then by 60 to get revolutions per minute.

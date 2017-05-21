#ifndef _SINE_GEN_H_
#define _SINE_GEN_H_

#include "MCP4821_driver.h"

volatile MCP4821_Data_t DAC_data;	// DAC data
volatile double ampl;

void SineGenInit();

#endif /* _SINE_GEN_H_ */
#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include "TC74_driver.h"

uint8_t status()
{
	uint8_t state = TWSR & 11111000;	//the status register, last 3 bits set to 0
	return state;
}

void TWI_init(void)
{
	// TODO:
	// Set Prescaler to 4
	TWSR |= 1 << TWPS0;
	TWSR &= ~(1 << TWPS1);

	// TODO:
	// Set SCL frequency = 16000000 / (16 + 2 * 48 * 4) = 40Khz // 48 = TWBR, 4 = prescaler
	//So set the correct register to 0x30
	TWBR = 48; // = 0x30  // = 0011 0000

	// TODO
	//Enable TWI
	TWCR |= 1 << TWEN;
}

void TWI_start(void)
{
	//TODO
	//Send start signal
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	// TODO:
	// Wait for TWINT Flag set. This indicates that
	//the START condition has been transmitted.
	while (!(TWCR & (1 << TWINT)));
}

void TWI_stop(void)
{
	//TODO
	//Send stop signal
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t TWI_read_ack(void)
{
	//TODO
	//Read byte with ACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}	


uint8_t TWI_read_nack(void)
{
	//TODO
	//Read byte with NACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWCR = (1 << TWINT) | (1 << TWEN);	
//	printf("\twaiting for TWINT flag, status %X\n", status());
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void TWI_write(uint8_t u8data)
{
	//TODO
	//Load DATA into TWDR Register. Clear TWINT
	//bit in TWCR to start transmission of data.
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWDR = u8data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

//TODO
//Write a function that communicates with the TC74A0.
//The function needs to take the address of the IC as a parameter.
//datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/21462D.pdf
//And returns with the temperature.
uint8_t read_temp(uint8_t address)
{
	uint8_t address_r = (address << 1) | 1; // | 0b00000001
	uint8_t address_w = (address << 1);
	
	TWI_start();
//	printf("\tstart sent, status %X\n", status());
//	printf("Sending IC address to write\n");	
	TWI_write(address_w);
//	printf("\tdata sent, status %X\n", status());
//	printf("Sending register address\n");	
	TWI_write(REG_ADDR);	//the command byte selects the register
//	printf("\tdata sent, status %X\n", status());
//	printf("Sending another start signal\n");
	TWI_start();
//	printf("\tstart sent, status %X\n", status());
//	printf("Sending IC address to read\n");
	TWI_write(address_r);
//	printf("\tdata sent, status %X\n", status());
//	printf("Getting temp data\n");
	uint8_t temp = TWI_read_nack();
//	printf("\tdata returned, status %X\n", status());
//	printf("Sending stop\n");
	TWI_stop();
//	printf("\tstop sent, status %X\n", status());
//	printf("Giving back temperature\n");	
	return temp;
}

//TODO Advanced:
//Calculate the average of the last 16 data, and return with that.
//TODO Advanced+:
//Select the outstanding (false) data before averaging it.
//This data is not needed, messes up your data, get rid of it.
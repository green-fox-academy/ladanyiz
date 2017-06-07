#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include "TC74_driver.h"

uint8_t status()
{
	uint8_t state = TWSR;	//the status register
	state &= 11111000;	//last 3 bits set to 0
	return state;
}

void TWI_init(void)
{
	// TODO:
	// Set Prescaler to 4
	TWSR |= 1 << TWPS0;
	TWSR &= ~(1 << TWPS1);

	// TODO:
	// Set SCL frequency = 16000000 / (16 + 2 * 48 * 4) = 40Khz
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
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	// TODO:
	// Wait for TWINT Flag set. This indicates that
	//the START condition has been transmitted.
	while (!(TWCR & (1 << TWINT)));
	printf("start sent, status %X\n", status());
}

void TWI_stop(void)
{
	//TODO
	//Send stop signal
	TWCR |= 1 << TWSTO;
	printf("stop sent, status %X\n", status());
}

uint8_t TWI_read_ack(void)
{
	//TODO
	//Read byte with ACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	uint8_t data;
	while (!(TWCR & (1 << TWINT)));
	data = TWDR;
	TWCR |= (1 << TWINT) | (1 << TWEA);
	return data;
}	


uint8_t TWI_read_nack(void)
{
	//TODO
	//Read byte with NACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWCR |= 1 << TWINT;	
	printf("waiting for TWINT flag, status %X\n", status());
	while (!(TWCR & (1 << TWINT)));
	printf("loading data, status %X\n", status());
	uint8_t data = TWDR;
	printf("returning with data, status %X\n", status());
	return data;
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
//	printf("data loaded, status %X\n", status());
	TWCR |= (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	printf("data sent, status %X\n", status());
}

//TODO
//Write a function that communicates with the TC74A0.
//The function needs to take the address of the IC as a parameter.
//datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/21462D.pdf
//And returns with the temperature.
uint8_t read_temp(uint8_t address)
{
	uint8_t address_r = (address << 1) | (0b00000001);
	uint8_t address_w = (address << 1);
	
	TWI_start();
	printf("sending IC address to write\n");	
	TWI_write(address_w);
	printf("sending register address\n");	
	TWI_write(temp_reg);	//the command byte selects register
	TWI_start();
	printf("sending IC address to read\n");
	TWI_write(address_r);
	printf("getting temp data\n");
	uint8_t temp = TWI_read_nack();
	printf("sending stop\n");
	TWI_stop();
	printf("giving back temperature\n");	
	return temp;
}

//TODO Advanced:
//Calculate the average of the last 16 data, and return with that.
//TODO Advanced+:
//Select the outstanding (false) data before averaging it.
//This data is not needed, messes up your data, get rid of it.
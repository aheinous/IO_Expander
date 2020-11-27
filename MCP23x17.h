#pragma once

#include <Arduino.h>


class MCP23x17{
private:
	uint16_t curMode;
	uint16_t curWrite;
	uint16_t curPullUp;

public:

	// raw read and write methods that actualy differ
	// between the MCP23017 (I2C) and the MCP23S17 (SPI)
	virtual uint8_t regRead_8(uint8_t regAddr) = 0;
	virtual void regWrite_8(uint8_t regAddr, uint8_t value) = 0;
	virtual uint16_t regRead_16(uint8_t regAddr) = 0;
	virtual void regWrite_16(uint8_t regAddr, uint16_t value) = 0;

	void begin();

	// All the methods below have implentations
	// common to both the MCP23S17 and the MCP23017.

	// single-bit Arduino-like versions
	void pinMode(uint8_t pin, uint8_t mode);
	void digitalWrite(uint8_t pin, uint8_t value);
	uint8_t digitalRead(uint8_t pin);
	void pullUp(uint8_t pin, uint8_t value);

	// 8-bit versions
	void pinMode_8(uint8_t port, uint8_t mode);
	void digitalWrite_8(uint8_t port, uint8_t value);
	uint8_t digitalRead_8(uint8_t port);
	void pullUp_8(uint8_t port, uint8_t value);

	// 16-bit versions
	void pinMode_16(uint16_t mode);
	void digitalWrite_16(uint16_t value);
	uint16_t digitalRead_16();
	void pullUp_16(uint16_t value);

};

#define MCP23x17_PORTA 0
#define MCP23x17_PORTB 1

#define MCP23x17_A0 0
#define MCP23x17_A1 1
#define MCP23x17_A2 2
#define MCP23x17_A3 3
#define MCP23x17_A4 4
#define MCP23x17_A5 5
#define MCP23x17_A6 6
#define MCP23x17_A7 7
#define MCP23x17_B0 8
#define MCP23x17_B1 9
#define MCP23x17_B2 10
#define MCP23x17_B3 11
#define MCP23x17_B4 12
#define MCP23x17_B5 13
#define MCP23x17_B6 15
#define MCP23x17_B7 15


#define MCP23x17_ADDRESS 0x20

// registers
#define MCP23x17_IODIRA 0x00
#define MCP23x17_IPOLA 0x02
#define MCP23x17_GPINTENA 0x04
#define MCP23x17_DEFVALA 0x06
#define MCP23x17_INTCONA 0x08
#define MCP23x17_IOCONA 0x0A
#define MCP23x17_GPPUA 0x0C
#define MCP23x17_INTFA 0x0E
#define MCP23x17_INTCAPA 0x10
#define MCP23x17_GPIOA 0x12
#define MCP23x17_OLATA 0x14


#define MCP23x17_IODIRB 0x01
#define MCP23x17_IPOLB 0x03
#define MCP23x17_GPINTENB 0x05
#define MCP23x17_DEFVALB 0x07
#define MCP23x17_INTCONB 0x09
#define MCP23x17_IOCONB 0x0B
#define MCP23x17_GPPUB 0x0D
#define MCP23x17_INTFB 0x0F
#define MCP23x17_INTCAPB 0x11
#define MCP23x17_GPIOB 0x13
#define MCP23x17_OLATB 0x15

#define MCP23x17_INT_ERR 255


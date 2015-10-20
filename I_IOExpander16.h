#ifndef I_IO_EXPANDER16_H
#define I_IO_EXPANDER16_H

#include <stdint.h>

// In 16 bit mode PORTB is bits 8-15 
// and PORTA is bits 0-7

#define IOEX16_PORTA 0
#define IOEX16_PORTB 1

#define IOEX16_A0 0
#define IOEX16_A1 1
#define IOEX16_A2 2
#define IOEX16_A3 3
#define IOEX16_A4 4
#define IOEX16_A5 5
#define IOEX16_A6 6
#define IOEX16_A7 7
#define IOEX16_B0 8
#define IOEX16_B1 9
#define IOEX16_B2 10
#define IOEX16_B3 11
#define IOEX16_B4 12
#define IOEX16_B5 13
#define IOEX16_B6 15
#define IOEX16_B7 15


class I_IOExpander16{
public:
	// arduino-like single bit methods
	virtual void pinMode(uint8_t pin, uint8_t mode) = 0;
	virtual void digitalWrite(uint8_t pin, uint8_t value) = 0;
	virtual uint8_t digitalRead(uint8_t pin) = 0;
	virtual void pullUp(uint8_t pin, uint8_t value) = 0;

	// 8-bit versions
	virtual void pinMode_8(uint8_t port, uint8_t mode) = 0;
	virtual void digitalWrite_8(uint8_t port, uint8_t value) = 0;
	virtual uint8_t digitalRead_8(uint8_t port) = 0;
	virtual void pullUp_8(uint8_t port, uint8_t value) = 0;

	// 16-bit versions
	virtual void pinMode_16(uint16_t mode) = 0;
	virtual void digitalWrite_16(uint16_t value) = 0;
	virtual uint16_t digitalRead_16() = 0;
	virtual void pullUp_16(uint16_t value) = 0;

};



#endif
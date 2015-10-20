#ifndef IO_EXPANDER16_MOCK_H
#define IO_EXPANDER16_MOCK_H

#include "I_IOExpander16.h"

class IOExpander16_mock : public I_IOExpander16 {
public:
	// IOExpander16_mock();
	// ~IOExpander16_mock();

	virtual void pinMode(uint8_t pin, uint8_t mode);
	virtual void digitalWrite(uint8_t pin, uint8_t value);
	virtual uint8_t digitalRead(uint8_t pin);
	virtual void pullUp(uint8_t pin, uint8_t value);

	// 8-bit versions
	virtual void pinMode_8(uint8_t port, uint8_t mode);
	virtual void digitalWrite_8(uint8_t port, uint8_t value);
	virtual uint8_t digitalRead_8(uint8_t port);
	virtual void pullUp_8(uint8_t port, uint8_t value);

	// 16-bit versions
	virtual void pinMode_16(uint16_t mode);
	virtual void digitalWrite_16(uint16_t value);
	virtual uint16_t digitalRead_16();
	virtual void pullUp_16(uint16_t value);
	
};


#endif // IO_EXPANDER16_MOCK_H

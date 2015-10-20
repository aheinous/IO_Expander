/*************************************************** 
  This is a library for the MCP23017 i2c port expander

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
/* Adapted by Alex Haynes from Adafruit MCP23017 lib */

#ifndef ALEX_MCP23017_H
#define ALEX_MCP23017_H

#include "MCP23x17.h"

#ifdef __AVR_ATtiny85__
#include <TinyWireM.h>
#else
#include <Wire.h>
#endif


class MCP23017 : public MCP23x17{
private:
	const uint8_t i2c_address;

protected:
	virtual uint8_t read_8(uint8_t regAddr);
	virtual void write_8(uint8_t regAddr, uint8_t value);
	virtual uint16_t read_16(uint8_t regAddr);
	virtual void write_16(uint8_t regAddr, uint16_t value);

public:
	MCP23017(uint8_t address);
	virtual void begin();
};

#endif
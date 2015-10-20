/* Adapted by Alex Haynes from Adafruit MCP23017 lib */

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

#include "MCP23017.h"
#include <Arduino.h>


#define MCP23017_ADDRESS 0x20

// minihelper to keep Arduino backward compatibility
static inline void wiresend(uint8_t x) {
#if ARDUINO >= 100
	Wire.write((uint8_t) x);
#else
	Wire.send(x);
#endif
}

// minihelper to keep Arduino backward compatibility
static inline uint8_t wirerecv(void) {
#if ARDUINO >= 100
	return Wire.read();
#else
	return Wire.receive();
#endif
}

// shutup compiler warning about ambiguous types
static inline uint8_t requestFrom(uint8_t from, uint8_t count){
	return Wire.requestFrom(from, count);
}

MCP23017::MCP23017(uint8_t address) : i2c_address(address | MCP23017_ADDRESS) {}


void MCP23017::begin(){
	Wire.begin();
	MCP23x17::begin();
}


void MCP23017::write_16(uint8_t regAddr, uint16_t value){
	Wire.beginTransmission(i2c_address);
	wiresend(regAddr);
	wiresend(value & 0xFF);
	wiresend(value >> 8);
	Wire.endTransmission();
}
uint16_t MCP23017::read_16(uint8_t regAddr){
	Wire.beginTransmission(i2c_address);
	wiresend(regAddr);
	Wire.endTransmission();

	requestFrom(i2c_address, 2);
	uint8_t a = wirerecv();
	uint16_t ba = wirerecv();
	ba <<= 8;
	ba |= a;

	return ba;
}

uint8_t MCP23017::read_8(uint8_t regAddr){
	Wire.beginTransmission(i2c_address);
	wiresend(regAddr);
	Wire.endTransmission();

	requestFrom(i2c_address, 1);
	return wirerecv();	
}

void MCP23017::write_8(uint8_t regAddr, uint8_t value){
	Wire.beginTransmission(i2c_address);
	wiresend(regAddr);
	wiresend(value);
	Wire.endTransmission();
}

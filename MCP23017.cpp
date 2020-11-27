/* Adapted by Alex Haynes from Adafruit MCP23017 lib */



#include "MCP23017.h"
#include <Arduino.h>


#define MCP23017_ADDRESS 0x20



// shutup compiler warning about ambiguous types
static inline uint8_t requestFrom(uint8_t from, uint8_t count){
	return Wire.requestFrom(from, count);
}

MCP23017::MCP23017(uint8_t address) : i2c_address(address | MCP23017_ADDRESS) {}


void MCP23017::begin(){
	Wire.begin();
	Wire.setClock(400000);
	MCP23x17::begin();
}


void MCP23017::regWrite_16(uint8_t regAddr, uint16_t value){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.write(value & 0xFF);
	Wire.write(value >> 8);
	Wire.endTransmission();
}
uint16_t MCP23017::regRead_16(uint8_t regAddr){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.endTransmission();

	requestFrom(i2c_address, 2);
	uint8_t a = Wire.read();
	uint16_t ba = Wire.read();
	ba <<= 8;
	ba |= a;

	return ba;
}

uint8_t MCP23017::regRead_8(uint8_t regAddr){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.endTransmission();

	requestFrom(i2c_address, 1);
	return Wire.read();	
}

void MCP23017::regWrite_8(uint8_t regAddr, uint8_t value){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission();
}

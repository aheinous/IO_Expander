

#include "MCP23017.h"
#include <Arduino.h>
#ifdef __AVR_ATtiny85__
#include <TinyWireM.h>
#else
#include <Wire.h>
#endif


#define MCP23017_ADDRESS 0x20



void _MCP23017_serialImpl::init(uint8_t address){
	i2c_address = (address | MCP23017_ADDRESS);
}


void _MCP23017_serialImpl::begin(){
	Wire.begin();
	Wire.setClock(400000);
}


void _MCP23017_serialImpl::regWrite_16(uint8_t regAddr, uint16_t value){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.write(value & 0xFF);
	Wire.write(value >> 8);
	Wire.endTransmission();
}
uint16_t _MCP23017_serialImpl::regRead_16(uint8_t regAddr){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.endTransmission();

	Wire.requestFrom(i2c_address, (uint8_t)2);
	uint8_t a = Wire.read();
	uint16_t ba = Wire.read();
	ba <<= 8;
	ba |= a;

	return ba;
}

uint8_t _MCP23017_serialImpl::regRead_8(uint8_t regAddr){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.endTransmission();

	Wire.requestFrom(i2c_address, (uint8_t)1);
	return Wire.read();	
}

void _MCP23017_serialImpl::regWrite_8(uint8_t regAddr, uint8_t value){
	Wire.beginTransmission(i2c_address);
	Wire.write(regAddr);
	Wire.write(value);
	Wire.endTransmission();
}

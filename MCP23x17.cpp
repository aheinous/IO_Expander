/* Adapted by Alex Haynes from Adafruit MCP23x17 lib */

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

#include "MCP23x17.h"
#include <Arduino.h>

void MCP23x17::begin(){
	// Wire.begin();
	// set all inputs
	curMode = 0xFFFF;
	curWrite = 0x0000;
	curPullUp = 0x0000;
	this->write_16(MCP23x17_IODIRA, 0xFFFF);
}

/////////////// arduino-like signal bit methods ///////////////

void MCP23x17::pinMode(uint8_t pin, uint8_t mode) {
	// update cached value
	if(mode==INPUT){
		// set bit
		curMode |= (1<<pin);
	}else{
		// clear bit
		curMode &= ~(1<<pin);
	}
	// send change to chip
	if(pin < 8){
		this->write_8(MCP23x17_IODIRA, curMode & 0xFF);
	}else{
		this->write_8(MCP23x17_IODIRB, curMode>>8);	
	}
}

void MCP23x17::digitalWrite(uint8_t pin, uint8_t value) {
	// update cached value
	if(value==HIGH){
		// set bit
		curWrite |= (1<<pin);
	}else{
		// clear bit
		curWrite &= ~(1<<pin);
	}
	// send change to chip
	if(pin < 8){
		this->write_8(MCP23x17_GPIOA, curWrite & 0xFF);
	}else{
		this->write_8(MCP23x17_GPIOB, curWrite>>8);	
	}
}

 void MCP23x17::pullUp(uint8_t pin, uint8_t value) {
 	// update cached value
 	if(value){
 		// set bit
 		curPullUp |= (1<<pin);
 	}else{
 		// clear bit
 		curPullUp &= ~(1<<pin);
 	}
 	// send change to chip
 	if(pin < 8){
 		this->write_8(MCP23x17_GPPUA, curPullUp & 0xFF);
 	}else{
 		this->write_8(MCP23x17_GPPUB, curPullUp>>8);	
 	}
 }

 uint8_t MCP23x17::digitalRead(uint8_t pin) {
 	uint8_t port = IOEX16_PORTA;
 	if(pin >= 8){
 		pin -= 8;
 		port = IOEX16_PORTB;
 	}
 	uint8_t vec = this->digitalRead_8(port);
 	return (vec & (1<<pin) ) ? HIGH : LOW;
 }

//////////////// 8-bit versions /////////////////

 void MCP23x17::pinMode_8(uint8_t port, uint8_t mode) {
 	if(port==IOEX16_PORTA){
	 	this->write_8( MCP23x17_IODIRA, mode);
	 	this->curMode = (this->curMode & 0xFF00) | mode;
	}else{
	 	this->write_8( MCP23x17_IODIRB, mode);
	 	this->curMode = (this->curMode & 0x00FF) | (mode<<8);
	} 	
 }

 void MCP23x17::digitalWrite_8(uint8_t port, uint8_t value) {
 	if(port==IOEX16_PORTA){
	 	this->write_8( MCP23x17_GPIOA, value);
	 	this->curWrite = (this->curWrite & 0xFF00) | value;
	}else{
	 	this->write_8( MCP23x17_GPIOB, value);
	 	this->curWrite = (this->curWrite & 0x00FF) | (value<<8);
	}
 }

 void MCP23x17::pullUp_8(uint8_t port, uint8_t value) {
	if(port==IOEX16_PORTA){
		this->write_8( MCP23x17_GPPUA, value);
		this->curPullUp = (this->curPullUp & 0xFF00) | value;
	}else{
		this->write_8( MCP23x17_GPPUB, value);
		this->curPullUp = (this->curPullUp & 0x00FF) | (value<<8);
	}
 }

 uint8_t MCP23x17::digitalRead_8(uint8_t port) {
 	if(port==IOEX16_PORTA){
 		return this->read_8(MCP23x17_GPIOA);
 	}
	return this->read_8(MCP23x17_GPIOB);
 }


/////////////////// 16-bit versions ///////////////////

 void MCP23x17::pinMode_16(uint16_t mode) {
 	this->write_16(MCP23x17_IODIRA, mode);
 	this->curMode = mode;
 }

 void MCP23x17::digitalWrite_16(uint16_t value) {
 	this->write_16(MCP23x17_GPIOA, value);
 	this->curWrite = value;
 }
 void MCP23x17::pullUp_16(uint16_t value) {
 	this->write_16(MCP23x17_GPPUA, value);
 	this->curPullUp = value;
 }

 uint16_t MCP23x17::digitalRead_16() {
 	return this->read_16(MCP23x17_GPIOA);
 }


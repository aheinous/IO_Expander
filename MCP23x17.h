#pragma once

#include <Arduino.h>


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



template<typename T>
class _MCP23x17 : public T{
private:
	uint16_t curMode;
	uint16_t curWrite;
	uint16_t curPullUp;

public:

	_MCP23x17(){}

	void begin(){
		T::begin();
		// set all inputs
		curMode = 0xFFFF;
		curWrite = 0x0000;
		curPullUp = 0x0000;
		this->regWrite_16(MCP23x17_IODIRA, 0xFFFF);
	}

	/////////////// arduino-like signal bit methods ///////////////

	void pinMode(uint8_t pin, uint8_t mode) {
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
			this->regWrite_8(MCP23x17_IODIRA, curMode & 0xFF);
		}else{
			this->regWrite_8(MCP23x17_IODIRB, curMode>>8);	
		}
	}

	void digitalWrite(uint8_t pin, uint8_t value) {
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
			this->regWrite_8(MCP23x17_GPIOA, curWrite & 0xFF);
		}else{
			this->regWrite_8(MCP23x17_GPIOB, curWrite>>8);	
		}
	}
	void pullUp(uint8_t pin, uint8_t value) {
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
			this->regWrite_8(MCP23x17_GPPUA, curPullUp & 0xFF);
		}else{
			this->regWrite_8(MCP23x17_GPPUB, curPullUp>>8);	
		}
	}

	uint8_t digitalRead(uint8_t pin) {
		uint8_t port = MCP23x17_PORTA;
		if(pin >= 8){
			pin -= 8;
			port = MCP23x17_PORTB;
		}
		uint8_t vec = this->digitalRead_8(port);
		return (vec & (1<<pin) ) ? HIGH : LOW;
	}


	//////////////// 8-bit versions /////////////////

	void pinMode_8(uint8_t port, uint8_t mode) {
		if(port==MCP23x17_PORTA){
			this->regWrite_8( MCP23x17_IODIRA, mode);
			this->curMode = (this->curMode & 0xFF00) | mode;
		}else{
			this->regWrite_8( MCP23x17_IODIRB, mode);
			this->curMode = (this->curMode & 0x00FF) | (mode<<8);
		} 	
	}

	void digitalWrite_8(uint8_t port, uint8_t value) {
		if(port==MCP23x17_PORTA){
			this->regWrite_8( MCP23x17_GPIOA, value);
			this->curWrite = (this->curWrite & 0xFF00) | value;
		}else{
			this->regWrite_8( MCP23x17_GPIOB, value);
			this->curWrite = (this->curWrite & 0x00FF) | (value<<8);
		}
	}

	void pullUp_8(uint8_t port, uint8_t value) {
		if(port==MCP23x17_PORTA){
			this->regWrite_8( MCP23x17_GPPUA, value);
			this->curPullUp = (this->curPullUp & 0xFF00) | value;
		}else{
			this->regWrite_8( MCP23x17_GPPUB, value);
			this->curPullUp = (this->curPullUp & 0x00FF) | (value<<8);
		}
	}

	uint8_t digitalRead_8(uint8_t port) {
		if(port==MCP23x17_PORTA){
			return this->regRead_8(MCP23x17_GPIOA);
		}
		return this->regRead_8(MCP23x17_GPIOB);
	}


	/////////////////// 16-bit versions ///////////////////

	void pinMode_16(uint16_t mode) {
		this->regWrite_16(MCP23x17_IODIRA, mode);
		this->curMode = mode;
	}

	void digitalWrite_16(uint16_t value) {
		this->regWrite_16(MCP23x17_GPIOA, value);
		this->curWrite = value;
	}
	void pullUp_16(uint16_t value) {
		this->regWrite_16(MCP23x17_GPPUA, value);
		this->curPullUp = value;
	}

	uint16_t digitalRead_16() {
		return this->regRead_16(MCP23x17_GPIOA);
	}

};


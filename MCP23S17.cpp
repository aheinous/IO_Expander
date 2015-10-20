/*************************************************** 
  This is a library for the MCP23S17 i2c port expander

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
/* Adapted by Alex Haynes from Adafruit MCP23S17 lib */

#include "MCP23S17.h"
#include <Arduino.h>


#define    CLOCK_DIVIDER (2)           
#define    OPCODEW       (0b01000000)
#define    OPCODER       (0b01000001)
#define    ADDR_ENABLE   (0b00001000)


// prevent this->digitalWrite() from being called instead
static inline void arduino_digitalWrite(uint8_t pin, uint8_t val){
	digitalWrite(pin, val);
}
// prevent this->digitalRead() from being called instead
static inline uint8_t arduino_digitalRead(uint8_t pin){
	return digitalRead(pin);
}
// prevent this->PinMode() from being called instead
static inline void arduino_pinMode(uint8_t pin, uint8_t mode){
	pinMode(pin, mode);
}


MCP23S17::MCP23S17(uint8_t address, uint8_t csPin) 
: 
opcodeWrite(address | OPCODEW),
opcodeRead(address | OPCODER),
csPin(csPin) 
{

}


void MCP23S17::begin(){
	arduino_pinMode(csPin, OUTPUT);
	arduino_digitalWrite(csPin, HIGH);
	SPI.begin();                         
	SPI.setClockDivider(CLOCK_DIVIDER);  
	SPI.setBitOrder(MSBFIRST);           
	SPI.setDataMode(SPI_MODE0);
	// enable HW addressing
	this->write_8(MCP23x17_IOCONA, ADDR_ENABLE); 
	MCP23x17::begin();
}

void MCP23S17::write_16(uint8_t regAddr, uint16_t word){

	arduino_digitalWrite(csPin, LOW);                            
	SPI.transfer(opcodeWrite);             
	SPI.transfer(regAddr);                 
	SPI.transfer(word & 0xFF);        
	SPI.transfer(word >> 8);   
	arduino_digitalWrite(csPin, HIGH);
}

uint16_t MCP23S17::read_16(uint8_t regAddr){
	uint16_t value = 0;                   
	arduino_digitalWrite(csPin, LOW);                     
	SPI.transfer(opcodeRead);  
	SPI.transfer(regAddr);                     
	value = SPI.transfer(0x00);      // dummy write  
	value |= (SPI.transfer(0x00) << 8);      
	arduino_digitalWrite(csPin, HIGH);
                    
	return value;   
}

uint8_t MCP23S17::read_8(uint8_t regAddr){
	uint8_t value = 0;                        
	arduino_digitalWrite(csPin, LOW);              
	SPI.transfer(opcodeRead);  
	SPI.transfer(regAddr);                   
	value = SPI.transfer(0x00);              
	arduino_digitalWrite(csPin, HIGH);
                
	return value;  
}

void MCP23S17::write_8(uint8_t regAddr, uint8_t value){
	arduino_digitalWrite(csPin, LOW);                  
	SPI.transfer(opcodeWrite);     
	SPI.transfer(regAddr);                           
	SPI.transfer(value);                      
	arduino_digitalWrite(csPin, HIGH);
}


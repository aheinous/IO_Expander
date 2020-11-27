

#include "MCP23S17.h"
#include <Arduino.h>
#include <SPI.h> 

#define    CLOCK_DIVIDER (2)           
#define    OPCODEW       (0b01000000)
#define    OPCODER       (0b01000001)
#define    ADDR_ENABLE   (0b00001000)



void _MCP23S17_serialImpl::init(uint8_t address, uint8_t csPin) {
	opcodeWrite = (address | OPCODEW);
	opcodeRead = (address | OPCODER);
	this->csPin = csPin;
}


void _MCP23S17_serialImpl::begin(){
	::pinMode(csPin, OUTPUT);
	::digitalWrite(csPin, HIGH);
	SPI.begin();                         
	SPI.setClockDivider(CLOCK_DIVIDER);  
	SPI.setBitOrder(MSBFIRST);           
	SPI.setDataMode(SPI_MODE0);
	// enable HW addressing
	this->regWrite_8(MCP23x17_IOCONA, ADDR_ENABLE); 
}

void _MCP23S17_serialImpl::regWrite_16(uint8_t regAddr, uint16_t word){

	::digitalWrite(csPin, LOW);                            
	SPI.transfer(opcodeWrite);             
	SPI.transfer(regAddr);                 
	SPI.transfer(word & 0xFF);        
	SPI.transfer(word >> 8);   
	::digitalWrite(csPin, HIGH);
}

uint16_t _MCP23S17_serialImpl::regRead_16(uint8_t regAddr){
	uint16_t value = 0;                   
	::digitalWrite(csPin, LOW);                     
	SPI.transfer(opcodeRead);  
	SPI.transfer(regAddr);                     
	value = SPI.transfer(0x00);      // dummy write  
	value |= (SPI.transfer(0x00) << 8);      
	::digitalWrite(csPin, HIGH);
                    
	return value;   
}

uint8_t _MCP23S17_serialImpl::regRead_8(uint8_t regAddr){
	uint8_t value = 0;                        
	::digitalWrite(csPin, LOW);              
	SPI.transfer(opcodeRead);  
	SPI.transfer(regAddr);                   
	value = SPI.transfer(0x00);              
	::digitalWrite(csPin, HIGH);
                
	return value;  
}

void _MCP23S17_serialImpl::regWrite_8(uint8_t regAddr, uint8_t value){
	::digitalWrite(csPin, LOW);                  
	SPI.transfer(opcodeWrite);     
	SPI.transfer(regAddr);                           
	SPI.transfer(value);                      
	::digitalWrite(csPin, HIGH);
}


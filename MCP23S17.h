
#pragma once

#include "MCP23x17.h"
#include <SPI.h> 




class MCP23S17 : public MCP23x17{
private:
	const uint8_t opcodeWrite;
	const uint8_t opcodeRead;
	const uint8_t csPin;

protected:
	virtual uint8_t regRead_8(uint8_t regAddr);
	virtual void regWrite_8(uint8_t regAddr, uint8_t value);
	virtual uint16_t regRead_16(uint8_t regAddr);
	virtual void regWrite_16(uint8_t regAddr, uint16_t value);

public:
	MCP23S17(uint8_t address, uint8_t csPin);
	void begin();
};
#pragma once

#include "MCP23x17.h"

class _MCP23S17_serialImpl{
private:
	uint8_t opcodeWrite;
	uint8_t opcodeRead;
	uint8_t csPin;

public:
	void init(uint8_t address, uint8_t csPin);
	void begin();
	uint8_t regRead_8(uint8_t regAddr);
	void regWrite_8(uint8_t regAddr, uint8_t value);
	uint16_t regRead_16(uint8_t regAddr);
	void regWrite_16(uint8_t regAddr, uint16_t value);
};


class MCP23S17 : public _MCP23x17<_MCP23S17_serialImpl>{
public:
	MCP23S17(uint8_t address, uint8_t csPin){
		init(address, csPin);
	}
};
#pragma once

#include "MCP23x17.h"


class _MCP23017_serialImpl {
private:
	uint8_t i2c_address;

public:
	void init(uint8_t addr);
	void begin();
	uint8_t regRead_8(uint8_t regAddr);
	void regWrite_8(uint8_t regAddr, uint8_t value);
	uint16_t regRead_16(uint8_t regAddr);
	void regWrite_16(uint8_t regAddr, uint16_t value);
};



class MCP23017 : public _MCP23x17<_MCP23017_serialImpl>{
public:
	MCP23017(uint8_t address) {
		init(address);
	}
};
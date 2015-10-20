// Basic Example. See I_IOExpander16.h for explanation
// of all available methods.


#include <Wire.h> // include both of these here to make Arduino IDE/makefile include them.
#include <SPI.h>  


// ------ MCP23S17 version -----------
#include <MCP23S17.h>

const uint8_t hwAddr = 0;
const uint8_t csPin = 53;
MCP23S17 expander(hwAddr, csPin);

// ------ MCP23017 version -----------
// #include <MCP23017.h>

// const uint8_t hwAddr = 0;
// MCP23017 expander(hwAddr);

void setup(){
	expander.begin();
	expander.pinMode_16(0x0000);
	expander.digitalWrite_16(0xAAAA);
}

void loop(){

}





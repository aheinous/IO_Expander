# IO_Expander

An Arduino library for the MCP23017 and MCP23S17 IO-expanders (I2C and SPI versions respectively). Features include a consistent, coherent API and the fact that all classes inherit from I_IOExpander16. This makes changing to a different IO Expander or using a mock IO Expander, such as for testing/debugging or Test Driven Development, trivial.  Much faster 8 and 16 bit versions of all pin manipulations methods are provided.
## INSTALL:

Copy the IO_Exapander folder to your Arduino libraries directory. For the Arduino IDE/makefile to find either MCP23017.h or MCP23S17.h they have to be in a folder named either MCP23017 or MCP23S17 respectively. You can either create multiple copies of the library or you can create some symlinks. If using Linux run these commands from the Arduino libraries directory:

ln -s -T `pwd`/IO_Expander MCP23017

ln -s -T `pwd`/IO_Expander MCP23S17


## USAGE:

See examples/basic for a hello world type example. See I_IOExpander16.h for an explanation of the available methods.

#include "IOExpander16_mock.h"
#include <Arduino.h>

void IOExpander16_mock::pinMode(uint8_t pin, uint8_t mode){
	Serial.print("pinMode(pin,mode): ");
	Serial.print(pin);
	Serial.print(", ");
	Serial.print(mode);
	Serial.print(" INPUT = ");
	Serial.println(INPUT);

}
void IOExpander16_mock::digitalWrite(uint8_t pin, uint8_t value){
	Serial.print("digitalWrite(pin,value): ");
	Serial.print(pin);
	Serial.print(", ");
	Serial.println(value);
}
uint8_t IOExpander16_mock::digitalRead(uint8_t pin){
	Serial.print("digitalRead(pin): ");
	Serial.println(pin);
	return 0;
}


void IOExpander16_mock::pullUp(uint8_t pin, uint8_t value){

}

// 8-bit versions
void IOExpander16_mock::pinMode_8(uint8_t port, uint8_t mode){
	Serial.print("pinMode_8(port,mode): ");
	Serial.print(port);
	Serial.print(", ");
	Serial.println(mode, BIN);
}

void IOExpander16_mock::digitalWrite_8(uint8_t port, uint8_t value){
	Serial.print("digitalWrite_8(port,value): ");
	Serial.print(port);
	Serial.print(", ");
	Serial.println(value, BIN);
}

uint8_t IOExpander16_mock::digitalRead_8(uint8_t port){
	Serial.print("digitalRead_8(port): ");
	Serial.println(port);
	return 0;

}
void IOExpander16_mock::pullUp_8(uint8_t port, uint8_t value){

}

// 16-bit versions
void IOExpander16_mock::pinMode_16(uint16_t mode){

}
void IOExpander16_mock::digitalWrite_16(uint16_t value){

}
uint16_t IOExpander16_mock::digitalRead_16(){
	return 0;
}
void IOExpander16_mock::pullUp_16(uint16_t value){

}
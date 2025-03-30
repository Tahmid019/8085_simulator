#pragma once
#include "Registers.h"
class ALU {
public:
	static uint8_t adc(Registers& reg, uint8_t value);
	static uint8_t add(Registers& reg, uint8_t value);
	static uint8_t ana(Registers& reg, uint8_t value); // AND
};
#pragma once
#include "Head_1.h"

/*

	FLAG: Sgn - Z - P - AC C

*/

struct RegisterPair {
	uint8_t low, high;
	
	uint16_t get() {
		return (high << 8) | low;
	}

	void set(uint16_t value) {
		low = value & 0x00FF;
		high = (value >> 8) & 0x00FF;
	}
};

struct Registers{
	uint8_t A, B, C, D, E, H, L;
	uint16_t PC, SP;
	uint8_t Flags;

	RegisterPair BC = { B, C };
	RegisterPair DE = { D, E };
	RegisterPair HL = { H, L };
};
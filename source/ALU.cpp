#include "index.h"

/*

	FLAG: Sgn - Z - P - AC C 

*/

uint8_t ALU::add(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A += value;

	if ((reg.A & 0x10000000) == 0x10000000) {
		reg.Flags |= 0x10000000;
	}

	if (reg.A == 0x00000000) {
		reg.Flags |= 0x00100000;
	}

	if (parity(reg.A)) {
		reg.Flags |= 0x00001000;
	}

	if (auxillaryCarry(temp, value)) {
		reg.Flags |= 0x00000010;
	}

	return reg.A;
}

uint8_t ALU::adc(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A += value;
	
	if ( (reg.A & 0x10000000) == 0x10000000 ) {
		reg.Flags |= 0x10000000;
	}

	if ( reg.A == 0x00000000 ) {
		reg.Flags |= 0x00100000;
	}

	if (parity(reg.A)) {
		reg.Flags |= 0x00001000;
	}

	if (auxillaryCarry(temp, value)) {
		reg.Flags |= 0x00000010;
	}

	if (carry(reg.A)) {
		reg.Flags |= 0x00000001;
	}

	return reg.A;
}

uint8_t ALU::ana(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A &= value;

	if ((reg.A & 0x10000000) == 0x10000000) {
		reg.Flags |= 0x10000000;
	}

	if (reg.A == 0x00000000) {
		reg.Flags |= 0x00100000;
	}

	if (parity(reg.A)) {
		reg.Flags |= 0x00001000;
	}

	if (auxillaryCarry(temp, value)) {
		reg.Flags |= 0x00000010;
	}

	if (carry(reg.A)) {
		reg.Flags |= 0x00000001;
	}
	return reg.A;
}


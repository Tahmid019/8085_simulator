#include "Head_1.h"
#include "ALU.h"
#include "utils.h"

/*

	FLAG: Sgn - Z - P - AC C 

*/

uint8_t ALU::add(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A += value;

	if ((reg.A & 0x80) == 0x80) {
		reg.Flags |= 0x80;
	}

	if (reg.A == 0x00) {
		reg.Flags |= 0x20;
	}

	if (parity(reg.A)) {
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(temp, value)) {
		reg.Flags |= 0x02;
	}

	return reg.A;
}

uint8_t ALU::adc(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A += value;
	
	if ( (reg.A & 0x80) == 0x80 ) {
		reg.Flags |= 0x80;
	}

	if ( reg.A == 0x00000000 ) {
		reg.Flags |= 0x20;
	}

	if (parity(reg.A)) {
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(temp, value)) {
		reg.Flags |= 0x02;
	}

	if (carry(reg.A)) {
		reg.Flags |= 0x01;
	}

	return reg.A;
}

uint8_t ALU::ana(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A &= value;

	if ((reg.A & 0x80) == 0x80) {
		reg.Flags |= 0x80;
	}

	if (reg.A == 0x00) {
		reg.Flags |= 0x20;
	}

	if (parity(reg.A)) {
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(temp, value)) {
		reg.Flags |= 0x02;
	}

	if (carry(reg.A)) {
		reg.Flags |= 0x01;
	}
	return reg.A;
}

uint8_t ALU::cmp(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A - value;

	if ((reg.A & 0x80) == 0x80) {
		reg.Flags |= 0x80;
	}

	if (temp == 0x00) {
		reg.Flags |= 0x20;
	}

	if (parity(temp)) {
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(reg.A, value)) {
		reg.Flags |= 0x02;
	}

	if (carry(temp)) {
		reg.Flags |= 0x01;
	}
	return temp;
}


uint8_t ALU::daa(Registers& reg) {
	uint8_t lsb = reg.A & 0x0F;
	uint8_t msb = reg.A >> 4;

	if (lsb > 9 || (reg.Flags | 0xfd)) { // AC
		reg.A += 0x06;
	}
	if (msb > 9 || (reg.Flags | 0xfe)) { // Carry
		reg.A += 0x60;
		(reg.A > 0xFF) ? (reg.Flags |= 0x01) : (reg.Flags &= 0xfe);
	}
	//reg.Flags = (reg.A == 0x00) ? (); // Z
	//reg.flags.S = (reg.A & 0x80) != 0;
	//reg.flags.P = __builtin_parity(reg.A);
	return reg.A;
}



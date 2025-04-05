#include "Head_1.h"
#include "ALU.h"
#include "utils.h"

/*

	FLAG: Sgn - Z - P - AC C 

*/

uint8_t ALU::add(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A += value;

	if ((reg.A & 0x80) == 0x80) { // Sgn
		reg.Flags |= 0x80;
	}

	if (reg.A == 0x00) { // Z
		reg.Flags |= 0x20;
	}

	if (parity(reg.A)) { // P
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(temp, value)) { // AC
		reg.Flags |= 0x02;
	}

	if (carry(reg.A)) { // Carry
		reg.Flags |= 0x01;
	}


	return reg.A;
}

uint8_t ALU::adc(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A += value;
	
	if ((reg.A & 0x80) == 0x80) { // Sgn
		reg.Flags |= 0x80;
	}

	if (reg.A == 0x00000000) { // Z
		reg.Flags |= 0x20;
	}

	if (parity(reg.A)) { // P
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(temp, value)) { // AC
		reg.Flags |= 0x02;
	}

	if (carry(reg.A)) { // Carry
		reg.Flags |= 0x01;
	}

	return reg.A;
}

uint8_t ALU::ana(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A;
	reg.A &= value;

	if ((reg.A & 0x80) == 0x80) { // Sgn
		reg.Flags |= 0x80;
	}

	if (reg.A == 0x00) { // Z
		reg.Flags |= 0x20;
	}

	if (parity(reg.A)) { // P
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(temp, value)) { // AC
		reg.Flags |= 0x02;
	}

	if (carry(reg.A)) { // Carry
		reg.Flags |= 0x01;
	}
	return reg.A;
}

uint8_t ALU::cmp(Registers& reg, uint8_t value) {
	uint8_t temp = reg.A - value;

	if ((reg.A & 0x80) == 0x80) { // Sgn
		reg.Flags |= 0x80;
	}

	if (temp == 0x00) { // Z
		reg.Flags |= 0x20;
	}

	if (parity(temp)) { // P
		reg.Flags |= 0x08;
	}

	if (auxillaryCarry(reg.A, value)) { // AC
		reg.Flags |= 0x02;
	}

	if (carry(temp)) { // Carry
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
	if (reg.A == 0x00) { // Z
		reg.Flags |= 0x20;
	}
	if (reg.A & 0x80) { // Sgn
		reg.Flags |= 0x80;
	}
	if (parity(reg.A)) { // P
		reg.Flags |= 0x08;
	}
	
	return reg.A;
}

uint16_t ALU::dad(Registers& reg, RegisterPair& regx) {
	uint32_t result = (reg.HL.get() + regx.get());
	if (result > 0xFFFF) { // carry
		reg.Flags |= 0x01;
	}
	reg.HL.set(result);
	return reg.HL.get();
}

uint8_t ALU::ora(Registers& reg, uint8_t value) {
	reg.A |= value;
	
	if ((reg.A & 0x80) == 0x80) { // Sgn
		reg.Flags |= 0x80;
	}
	if (reg.A == 0x00) { // Z
		reg.Flags |= 0x20;
	}
	if (parity(reg.A)) { // P
		reg.Flags |= 0x08;
	}
	reg.Flags &= 0xFD; // AC
	reg.Flags &= 0xFE; // C
	return reg.A;
}



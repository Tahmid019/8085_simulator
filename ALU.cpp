#include "Head_1.h"
#include "ALU.h"
#include "utils.h"

/*

	FLAG: Sgn - Z - P - AC C 

*/

uint8_t ALU::add(Registers& reg, uint8_t value) {
	uint16_t temp = reg.A + value;
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

	if (temp > 0xFF) { // Carry
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

	if (reg.A < value) { // Carry
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
	reg.HL.set(result & 0XFFFF);
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

uint8_t ALU::sub(Registers& reg, uint8_t value) {
	if (reg.A < value) {
		reg.A = value - reg.A;
		reg.A = (~reg.A) & 0xFF;
		reg.A++;
		reg.Flags |= 0x01; // C
	}
	else {
		reg.A -= value;
		reg.Flags &= 0xFE; // C
	}
	reg.A &= 0xFF;
	uint16_t result = reg.A & 0xFF;

	//reg.Flags = (reg.Flags & 0xFE) | ((result & 0x100) != 0); // C
	reg.Flags = (reg.Flags & 0xDF) | (((result & 0xFF) == 0) << 5); // Z
	reg.Flags = (reg.Flags & 0x7F) | ((result & 0x80)); // Sgn
	reg.Flags = (reg.Flags & 0xF7) | (parity(result & 0xFF) << 3); // P

	return result & 0xFF;
}

uint8_t ALU::sbi(Registers& reg, uint8_t value) {
	uint8_t borrow = reg.Flags & 0x01;
	reg.A = (ALU::sub(reg, value) & 0xFF);
	
	(borrow) ? reg.A-- : reg.A;

	return reg.A & 0xFF;
}

uint8_t ALU::xra(Registers& reg, uint8_t value) {
	reg.A ^= value;

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



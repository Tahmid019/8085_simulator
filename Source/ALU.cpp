#include "../Headers/Head_1.h"
#include "../Headers/ALU.h"
#include "../Headers/utils.h"

/*

	FLAG: Sgn - Z - P - AC C 

*/

uint8_t ALU::add(Registers& reg, uint8_t value) {
	uint16_t temp = static_cast<uint16_t>(reg.A) + static_cast<uint16_t>(value);
	reg.A = static_cast<uint8_t>(temp);

	reg.Flags &= ~(0x80 | 0x20 | 0x08 | 0x02 | 0x01);

	if (reg.A & 0x80) // Sgn
		reg.Flags |= 0x80;

	if (reg.A == 0x00) // Z
		reg.Flags |= 0x20;

	if (parity<uint8_t>(reg.A)) // P
		reg.Flags |= 0x08;

	if (auxillaryCarry<uint8_t>(static_cast<uint8_t>(temp), value)) // AC
		reg.Flags |= 0x02;

	if (temp > 0xFF) // Carry
		reg.Flags |= 0x01;

	return reg.A;
}


uint8_t ALU::adc(Registers& reg, uint8_t value) {
	uint8_t carryIn = (reg.Flags & 0x01) ? 1 : 0;

	uint16_t result = static_cast<uint16_t>(reg.A) + value + carryIn;
	uint8_t oldA = reg.A;
	reg.A = static_cast<uint8_t>(result);

	reg.Flags &= ~(0x80 | 0x20 | 0x08 | 0x02 | 0x01); // S, Z, P, AC, CY

	if (reg.A & 0x80) // Sng
		reg.Flags |= 0x80;

	if (reg.A == 0) // Z
		reg.Flags |= 0x20;

	if (parity<uint8_t>(reg.A)) // P
		reg.Flags |= 0x08;

	if (auxillaryCarry<uint8_t>(static_cast<uint8_t>(oldA + carryIn), value)) // AC
		reg.Flags |= 0x02;

	if (result > 0xFF) // C
		reg.Flags |= 0x01;

	return reg.A;
}


uint8_t ALU::ana(Registers& reg, uint8_t value) {
	cout << reg.A << endl;
	reg.A &= value;
	cout << reg.A << endl;

	// S, Z, P, AC, CY
	reg.Flags &= ~(0x80 | 0x20 | 0x08 | 0x02 | 0x01);

	if (reg.A & 0x80) // Sgn
		reg.Flags |= 0x80;

	if (reg.A == 0) // Z
		reg.Flags |= 0x20;

	if (parity<uint8_t>(reg.A)) // P
		reg.Flags |= 0x08;

	if ((reg.A | value) & 0x08) // AC
		reg.Flags |= 0x02;

	return reg.A;
}


uint8_t ALU::cmp(Registers& reg, uint8_t value) {
	uint8_t result = reg.A - value;

	reg.Flags &= ~(0x80 | 0x20 | 0x08 | 0x02 | 0x01);

	if (result & 0x80) // Sng
		reg.Flags |= 0x80;

	if (result == 0) // Z
		reg.Flags |= 0x20;

	if (parity<uint8_t>(result)) // P
		reg.Flags |= 0x08;

	if ((reg.A & 0x0F) < (value & 0x0F)) // AC
		reg.Flags |= 0x02;

	if (reg.A < value) // C
		reg.Flags |= 0x01;

	return result;
}



uint8_t ALU::daa(Registers& reg) {
	bool carrySet = false;

	// lower nibble
	if ((reg.A & 0x0F) > 9 || (reg.Flags & 0x04)) {
		if (auxillaryCarry<uint8_t>(reg.A, 0x06))
			reg.Flags |= 0x04;
		else
			reg.Flags &= ~0x04;

		reg.A += 0x06;
	}

	// upper nibble
	if ((reg.A >> 4) > 9 || (reg.Flags & 0x01)) {
		reg.A += 0x60;
		carrySet = true;
	}

	if (carrySet) // C
		reg.Flags |= 0x01;
	else
		reg.Flags &= ~0x01;

	updateFlags<uint8_t>(reg, reg.A, 0xA8); // SZP

	return reg.A;
}


uint16_t ALU::dad(Registers& reg, RegisterPair& regx) { 
	uint32_t result = reg.HL.get() + regx.get();

	if (result > 0xFFFF) // C
		reg.Flags |= 0x01;
	else
		reg.Flags &= ~0x01;

	reg.HL.set(static_cast<uint16_t>(result));

	reg.H = (reg.HL.get() >> 8) & 0xFF;
	reg.L = reg.HL.get() & 0xFF;

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
	if (parity<uint8_t>(reg.A)) { // P
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
	reg.Flags = (reg.Flags & 0xF7) | (parity<uint8_t>(result & 0xFF) << 3); // P

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
	if (parity<uint8_t>(reg.A)) { // P
		reg.Flags |= 0x08;
	}
	reg.Flags &= 0xFD; // AC
	reg.Flags &= 0xFE; // C
	return reg.A;
}



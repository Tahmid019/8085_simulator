#include "ALU.h"

void ALU::add(Registers& reg, uint8_t value) {
	reg.A += value;
}
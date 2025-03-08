#pragma once
#include "Memory.h"
#include "Registers.h"
#include "ALU.h"

class CPU {
public:
	Registers reg;
	Memory memory;
	int execute(uint8_t opcode);
};
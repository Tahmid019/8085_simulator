#pragma once
#include "Master.h"

class CPU {
public:
	Registers reg;
	Memory memory;
	int execute(uint8_t opcode);
};
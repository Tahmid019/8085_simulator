#pragma once
#include "Memory.h"
#include "Registers.h"
#include "ALU.h"
#include "InterruptControl.h"

class CPU {
public:
	Registers reg;
	Memory memory;
	InterruptControl interruptControl;
	int execute(uint8_t opcode);
};
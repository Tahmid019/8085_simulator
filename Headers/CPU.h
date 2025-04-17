#pragma once
#include "Memory.h"
#include "Registers.h"
#include "ALU.h"
#include "InterruptControl.h"
#include "IO.h"

class CPU {
public:
	Registers reg;
	Memory memory;
	InterruptControl interruptControl;
	IO io;
	int execute(uint8_t opcode);
};
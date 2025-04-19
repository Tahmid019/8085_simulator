#pragma once
#include "CPU.h"
#include <fstream>

class IOHandler {
public:
	void initializeData2Memory(CPU& cpu);
	void loadProgram(CPU& cpu, string filename, uint16_t& init_addr);
};
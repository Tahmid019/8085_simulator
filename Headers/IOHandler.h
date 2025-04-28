#pragma once
#include "CPU.h"
#include <fstream>

class IOHandler {
public:
	void initializeData2Memory(CPU& cpu, const string& mem_file);
	void loadProgram(CPU& cpu, string filename, uint16_t& init_addr);
};
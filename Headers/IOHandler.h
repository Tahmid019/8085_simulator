#pragma once
#include "CPU.h"
#include <fstream>

class IOHandler {
public:
	void initializeData2Memory(CPU& cpu, const string& mem_file);
	void loadProgramFile(CPU& cpu, string filename, uint16_t& init_addr);
	void loadProgram(CPU& cpu, vector<string>& assembled_code, uint16_t& init_addr);
};
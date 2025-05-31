#pragma once
#include "CPU.h"
#include <fstream>

class IOHandler {
public:
	void loadProgram(CPU& cpu, vector<string>& assembled_code, uint16_t& init_addr);
};
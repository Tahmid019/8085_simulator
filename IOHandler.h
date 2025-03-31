#pragma once
#include "CPU.h"
#include <fstream>

class IOHandler {
public:
	void loadProgram(string filename, CPU& cpu);
};
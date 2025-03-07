#pragma once
#include "CPU.h"
#include <fstream>

class IOHandler {
public:
	static void loadProgram(const char* filename, CPU& cpu);
};
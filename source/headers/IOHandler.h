#pragma once
#include "Master.h"

class IOHandler {
public:
	static void loadProgram(const char* filename, CPU& cpu);
};
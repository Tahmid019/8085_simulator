#pragma once
#include "Head_1.h"

class Memory {
public:
	Memory();
	~Memory() = default;

	std::map<uint16_t, uint8_t> mem;
	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);
	void clear();
};




#pragma once
#include <map>
#include <cstdint>

class Memory {
public:
	std::map<uint16_t, uint8_t> mem;
	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);
};
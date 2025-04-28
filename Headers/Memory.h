#pragma once
#include "Head_1.h"

class Memory {
public:
	vector<uint8_t> mem;
	
	Memory();
	
	void loadMemory(const string& mem_file);
	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);
	void clear();
	
	~Memory() = default;

	void save2csv(const string& filename);
};




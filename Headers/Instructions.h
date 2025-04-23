#pragma once
#include "Head_1.h"

class Instruction {
public:
	string mnemonic;
	function<vector<uint8_t>(const vector<string>&)> decoder;
	int wordSize;

	Instruction() = default;
	Instruction(string name, function<vector<uint8_t>(const vector<string>&)> decoder, uint8_t size)
		: name(move(name)), decoder(move(decoder)), wordSize(size) {}
};

extern map<string, Instruction> instructionSet;


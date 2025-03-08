#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

class Instruction {
public:
	std::string mnemonic;
	uint8_t opcode;
	int wordSize;

	Instruction() : mnemonic(""), opcode(0), wordSize(0) {}

	Instruction(std::string mn, uint8_t oc, int ws) : mnemonic(mn), opcode(oc), wordSize(ws) {}
	//static void Execute(std::string mnemonic);
};

extern std::unordered_map<std::string, Instruction> instructionSet;
extern std::unordered_map<std::string, std::function<void()>> instructionHandlers;
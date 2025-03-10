#pragma once
#include <iostream>
#include <string>

void debug(std::string mn, uint8_t reg);

void message(std::string msg, uint8_t mem);

bool parity(uint8_t val);

bool auxillaryCarry(uint8_t regValue_1, uint8_t regValue_2);

bool carry(uint8_t value);
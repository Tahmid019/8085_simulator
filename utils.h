#pragma once
#include <iostream>
#include <string>

typedef enum class MessageType {
    INFO,
    WARNING,
    ERROR,
    MEMORY,
    REGISTER
} MessageType;

void message(std::string msg, uint8_t in_load);

bool parity(uint8_t val);

bool auxillaryCarry(uint8_t regValue_1, uint8_t regValue_2);

bool carry(uint8_t value);
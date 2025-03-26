#pragma once
#include <iostream>
#include <string>

enum class MessageType {
    INFO,
    WARNING,
    ERROR,
    MEMORY,
    REGISTER
};

void message(std::string msg, uint8_t in_load, uint8_t out_load, MessageType type);

void debug(std::string msg, uint16_t in_addr, uint8_t in_data, MessageType type);

bool parity(uint8_t val);

bool auxillaryCarry(uint8_t regValue_1, uint8_t regValue_2);

bool carry(uint8_t value);
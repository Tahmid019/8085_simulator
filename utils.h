#pragma once
#include "Head_1.h"

enum class MessageType {
    INFO,
    WARNING,
    ERROR,
    MEMORY,
    REGISTER
};

enum class Type2Tpe {
    t8_2_8,
	t8_2_16,
	t16_2_8,
	t16_2_16
};



void message(std::string msg, uint8_t in_load, uint8_t out_load, MessageType type);

void debug(std::string msg, uint16_t in_addr, uint8_t in_data, MessageType type);

bool parity(uint8_t val);

bool auxillaryCarry(uint8_t regValue_1, uint8_t regValue_2);

bool carry(uint8_t value);

size_t t2t_message(string message, uint16_t a, uint16_t b, Type2Tpe type);
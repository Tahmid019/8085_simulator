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

void removeTrailingSpaces(string& str);

void debug(std::string msg, uint16_t in_addr, uint8_t in_data, MessageType type);

bool carry(uint8_t value);

size_t t2t_message(string message, uint16_t a, uint16_t b, Type2Tpe type);

uint8_t hto8b(const string& hexStr);


template<typename T>
bool parity(T val) {
    static_assert(std::is_unsigned<T>::value, "Only unsigned types are allowed");

    int count_1s = 0;
    for (int i = 0; i < sizeof(T) * 8; ++i) {
        if ((val >> i) & 1)
            ++count_1s;
    }

    return (count_1s % 2 == 0); // true == even 
}

template<typename T>
bool auxillaryCarry(T a, T b) {
    static_assert(std::is_unsigned<T>::value, "Only unsigned types are allowed");

    // bit 3 to 4, nibble carry
    return (((a & 0x0F) + (b & 0x0F)) & 0x10) != 0;
}

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



void message(string msg, uint8_t in_load, uint8_t out_load, MessageType type);

void removeTrailingSpaces(string& str);

void debug(string msg, uint16_t in_addr, uint8_t in_data, MessageType type);

bool carry(uint8_t value);

size_t t2t_message(string message, uint16_t a, uint16_t b, Type2Tpe type);

uint8_t hto8b(const string& hexStr);


template<typename T>
bool parity(T val) {
    static_assert(is_unsigned<T>::value, "Only unsigned types are allowed");

    int count_1s = 0;
    for (int i = 0; i < sizeof(T) * 8; ++i) {
        if ((val >> i) & 1)
            ++count_1s;
    }

    return (count_1s % 2 == 0); // true == even 
}

template<typename T>
bool auxillaryCarry(T a, T b) {
    static_assert(is_unsigned<T>::value, "Only unsigned types are allowed");

    // bit 3 to 4, nibble carry
    return (((a & 0x0F) + (b & 0x0F)) & 0x10) != 0;
}


template<typename T>
T ston(const string& data) {
    T value;
    if (data.back() == 'H') {
        data.pop_back();  

        if constexpr (sizeof(T) == 1) {
            value = static_cast<T>(hto8b(data));
        }
        else if constexpr (sizeof(T) == 2) {
            string high_str = "";
            reverse(data.begin(), data.end());
            while (data.size() > 2) {
                high_str.push_back(data.back());
                data.pop_back();
            }
            reverse(data.begin(), data.end());
            reverse(high_str.begin(), high_str.end());
            T low = static_cast<T>(hto8b(data));
            T high = static_cast<T>(hto8b(high_str));
            value = static_cast<T>((high << 8) & 0xFF00 | (low) & 0x00FF);
        }
        else {
            static_assert(sizeof(T) <= 2, "ston supports only 8 or 16 bit types");
        }

    }
    else {
        if constexpr (sizeof(T) == 1) {
            value = static_cast<T>(stoul(data, nullptr, 10));
        }
        else if constexpr (sizeof(T) == 2){
            string high_str = "";
            reverse(data.begin(), data.end());
            while (data.size() > 2) {
                high_str.push_back(data.back());
                data.pop_back();
            }
            reverse(data.begin(), data.end());
            reverse(high_str.begin(), high_str.end());
            T low = static_cast<T>(stoul(data, nullptr, 10));
            T high = static_cast<T>(stoul(high_str, nullptr, 10));
            value = static_cast<T>((high << 8) & 0xFF00 | (low) & 0x00FF);
        }
    }
    return value;
}


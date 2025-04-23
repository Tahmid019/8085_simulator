#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeCALL(const vector<string>& operands) {
    if (operands.size() != 1)
        throw runtime_error("CALL requires one 16-bit address operand");

    string data = operands[0];
    if (data.back() == 'H') data.pop_back();

    uint16_t address = static_cast<uint16_t>(stoi(data, nullptr, 16));
    uint8_t low = address & 0xFF;
    uint8_t high = (address >> 8) & 0xFF;

    return { 0xCD, low, high }; 
}

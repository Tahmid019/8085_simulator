#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeANI(const vector<string>& operands) {
    if (operands.size() != 1)
        throw runtime_error("ANI requires one immediate operand");

    string data = operands[0];
    if (data.back() == 'H') data.pop_back();

    uint8_t byte = static_cast<uint8_t>(stoi(data, nullptr, 16));

    return { 0xE6, byte };
}

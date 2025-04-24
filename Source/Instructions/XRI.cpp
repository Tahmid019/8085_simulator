#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeXRI(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("XRI instruction requires exactly one operand.");
    }
    int data = stoi(operands[0], nullptr, 0);
    return { 0xEE, static_cast<uint8_t>(data & 0xFF) };
}

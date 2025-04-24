#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSUI(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("SUI instruction requires exactly one operand.");
    }
    int data = stoi(operands[0], nullptr, 0);
    return { 0xD6, static_cast<uint8_t>(data & 0xFF) };
}

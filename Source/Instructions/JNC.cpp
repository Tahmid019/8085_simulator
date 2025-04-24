#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeJNC(const vector<string>& operands) {
    if (operands.size() != 1) {
        throw invalid_argument("JNC instruction requires exactly one operand.");
    }
    int addr = stoi(operands[0], nullptr, 0);
    return { 0xD2, static_cast<uint8_t>(addr & 0xFF), static_cast<uint8_t>((addr >> 8) & 0xFF) };
}

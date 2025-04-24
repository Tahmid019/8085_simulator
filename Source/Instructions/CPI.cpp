#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeCPI(const vector<string>& operands) {
    if (operands.empty()) throw invalid_argument("CPI requires one operand.");
    return { 0xFE, static_cast<uint8_t>(stoi(operands[0], nullptr, 0)) };
}


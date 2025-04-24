#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeRST(const vector<string>& operands) {
    int num = stoi(operands[0], nullptr, 0);
    if (num < 0 || num > 7) {
        throw invalid_argument("RST operand must be between 0 and 7.");
    }
    return { static_cast<uint8_t>(0xC7 + (num << 3)) };
}

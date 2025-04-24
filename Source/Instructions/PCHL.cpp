#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodePCHL(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("PCHL instruction takes no operands.");
    }
    return { 0xE9 };
}

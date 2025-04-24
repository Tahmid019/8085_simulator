#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeSPHL(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("SPHL instruction takes no operands.");
    }
return { 0xF9 };
}

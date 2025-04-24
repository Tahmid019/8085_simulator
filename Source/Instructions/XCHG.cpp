#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeXCHG(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("XCHG instruction takes no operands.");
    }
    return { 0xEB };
}

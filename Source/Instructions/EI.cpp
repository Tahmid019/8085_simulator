#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeEI(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("EI instruction takes no operands.");
    }

    return { 0xFB };
}


#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeDI(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("DI instruction takes no operands.");
    }

    return { 0xF3 };
}

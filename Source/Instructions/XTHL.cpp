#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeXTHL(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("XTHL instruction takes no operands.");
    }
    return { 0xE3 };
}

#pragma once
#include "../Headers/Head_2.h"

vector<uint8_t> decodeHLT(const vector<string>& operands) {
    if (!operands.empty()) {
        throw invalid_argument("HLT instruction takes no operands.");
    }

    return { 0x76 };
}

